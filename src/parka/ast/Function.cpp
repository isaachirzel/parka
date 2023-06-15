#include "parka/ast/Function.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/BlockExpression.hpp"

namespace parka
{
	FunctionSyntax::FunctionSyntax(PrototypeSyntax&& prototype, ExpressionSyntax& body) :
	_prototype(std::move(prototype)),
	_body(body),
	_parent(nullptr),
	_symbols()
	{}

	FunctionContext::FunctionContext(PrototypeContext&& prototype, ExpressionContext& body) :
	_prototype(std::move(prototype)),
	_body(body)
	{}

	static ExpressionSyntax *parseFunctionBody(Token& token)
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			token.increment();

			auto body = ExpressionSyntax::parse(token);

			if (!body)
				return {};

			if (token.type() != TokenType::Semicolon)
			{
				log::parseError(token, "';'", "Inline function bodies need to be ended with ';'.");
				return {};
			}

			token.increment();

			return body;
		}

		if (token.type() == TokenType::LeftBrace)
			return BlockExpressionSyntax::parse(token);
		
		log::parseError(token, "function body", "Functions require a body.");

		return {};
	}

	FunctionSyntax *FunctionSyntax::parse(Token& token)
	{
		auto prototype = PrototypeSyntax::parse(token);

		if (!prototype)
			return {};

		auto body = parseFunctionBody(token);

		if (!body)
			return {};

		auto *syntax = new FunctionSyntax(*prototype, *body);

		return syntax;
	}

	FunctionContext *FunctionSyntax::validate()
	{
		// TODO: Mutex

		auto prototype = _prototype.validate(*this);
		auto *body = _body.validate(*this);

		if (!prototype || !body)
			return {};

		auto *context = new FunctionContext(*prototype, *body);

		return context;
	}

	bool FunctionSyntax::declareSelf(SymbolTable& parent)
	{
		_parent = &parent;

		return parent.declare(*this);
	}

	bool FunctionSyntax::declare(EntitySyntax& entity)
	{
		const auto& name = entity.name();

		for (const auto *symbol : _symbols)
		{
			if (name == symbol->name())
			{
				log::error("A $ `$` has already been declared in this function.", entity.entityType(), name);
				// TODO: maybe just insert it anyways?
				return false;
			}
		}

		_symbols.push(&entity);
		
		return true;
	}

	EntitySyntax *FunctionSyntax::resolve(const Identifier& identifier)
	{
		const auto& name = identifier.text();
		// TODO: Iterate in reverse
		for (auto *entity : _symbols)
		{
			if (entity->name() == name)
				return entity;
		}

		return nullptr;
	}

	EntitySyntax *FunctionSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		if (identifier.isAbsolute() || identifier.length() > 1)
			return _parent->resolve(identifier);

		auto *local = resolve(identifier[0]);

		if (local != nullptr)
			return local;

		auto *global = _parent->resolve(identifier);

		return global;
	}

	std::ostream& operator<<(std::ostream& out, const FunctionSyntax& syntax)
	{
		out << syntax._prototype;

		return out;
	}
}
