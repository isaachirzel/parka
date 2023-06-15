#include "parka/ast/Function.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/Package.hpp"

namespace parka
{
	FunctionSyntax::FunctionSyntax(PrototypeSyntax&& prototype, ExpressionSyntax& body) :
	_prototype(std::move(prototype)),
	_body(body),
	_parent(nullptr),
	_symbols()
	{}

	FunctionContext::FunctionContext(String&& symbol, PrototypeContext&& prototype, ExpressionContext& body) :
	_symbol(std::move(symbol)),
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

		auto *context = new FunctionContext(getSymbol(), *prototype, *body);

		return context;
	}

	bool FunctionSyntax::declareSelf(PackageSyntax& parent)
	{
		_parent = &parent;

		return parent.declare(*this);
	}

	bool FunctionSyntax::declare(EntitySyntax& entity)
	{
		const auto& identifier = entity.identifier();
		const auto& name = identifier.text();

		for (auto *symbol : _symbols)
		{
			if (name == symbol->name())
			{
				log::error(identifier.token(), "A $ `$` has already been declared in this function.", entity.entityType(), name);

				auto *previous = dynamic_cast<EntitySyntax*>(symbol);

				if (previous != nullptr)
					log::note(previous->identifier().token(), "Previous declaration here:");
				// TODO: maybe just insert it anyways?
				return false;
			}
		}

		_symbols.push(&entity);
		
		return true;
	}

	EntityEntry *FunctionSyntax::find(const Identifier& identifier)
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

	EntityContext *FunctionSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		if (identifier.isAbsolute() || identifier.length() > 1)
			return _parent->resolve(identifier);

		auto *local = find(identifier[0]);

		if (local != nullptr)
			return local->context();

		auto *global = _parent->resolve(identifier);

		return global;
	}

	String FunctionSyntax::getSymbol() const
	{
		assert(_parent != nullptr);

		auto symbol = _parent->getSymbol();

		symbol += "::";
		symbol += name();

		return symbol;
	}

	std::ostream& operator<<(std::ostream& out, const FunctionSyntax& syntax)
	{
		out << syntax._prototype;

		return out;
	}
}
