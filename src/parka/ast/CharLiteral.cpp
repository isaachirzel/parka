#include "parka/ast/CharLiteral.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	static Optional<char> parseChar(Token& token)
	{
		if (token.type() != TokenType::CharacterLiteral)
		{
			log::parseError(token, "character");
			return {};
		}

		if (token.snippet().length() != 3)
		{
			log::error(token, "character literals may only contain 1 character", nullptr);
			return {};
		}

		auto character = token[0];

		return character;
	}

	ExpressionAst *CharLiteralAst::parse(Token& token)
	{
		auto value = parseChar(token);

		if (!value)
			return {};

		auto *syntax = new CharLiteralAst(token, *value);

		token.increment();

		return syntax;
	}

	ir::ExpressionIr *CharLiteralAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
