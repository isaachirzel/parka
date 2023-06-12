#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/BlockExpressionSyntax.hpp"

namespace parka
{
	FunctionSyntax::FunctionSyntax(PrototypeSyntax&& prototype, ExpressionSyntax& body) :
	_prototype(std::move(prototype)),
	_body(body),
	_parent(nullptr),
	_symbols()
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

	bool FunctionSyntax::declare(EntitySyntax& entity)
	{
		const auto& identifier = entity.identifier();

		for (const auto *symbol : _symbols)
		{
			if (identifier == symbol->identifier())
			{
				log::error("A parameter with the name `$` has already been declared in this prototype.", identifier);
				// TODO: maybe just insert it anyways?
				return false;
			}
		}

		_symbols.push(&entity);
		
		return true;
	}

	const EntityContext *FunctionSyntax::resolve(const Identifier& identifier)
	{
		log::notImplemented(here());
	}

	const EntityContext *FunctionSyntax::resolve(const QualifiedIdentifier& identifier)
	{
		log::notImplemented(here());
	}
}
