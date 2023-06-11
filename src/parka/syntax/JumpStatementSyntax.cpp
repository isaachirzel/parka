#include "parka/syntax/JumpStatementSyntax.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	static Optional<JumpType> getJumpType(Token& token)
	{
		auto keywordType = KeywordSyntax::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Return:
				return JumpType::Return;

			case KeywordType::Break:
				return JumpType::Break;

			case KeywordType::Continue:
				return JumpType::Continue;

			case KeywordType::Yield:
				return JumpType::Yield;

			default:
				log::parseError(token, "`return`, `break`, `continue` or `yield`");
				return {};
		}
	}

	StatementSyntax *JumpStatementSyntax::parse(Token& token)
	{
		auto type = getJumpType(token);

		if (!type)
			return {};

		// auto name = token;

		token.increment();

		ExpressionSyntax *value = nullptr;

		if (token.type() != TokenType::Semicolon)
		{
			switch (*type)
			{
				case JumpType::Continue:
					// TODO: Implement continuing on labels
					log::error(token, "Continue statements cannot have a value.");
					return {};
				
				case JumpType::Break:
					log::error(token, "Break statements cannot have a value.");
					return {};

				default:
					break;
			}
			
			value = ExpressionSyntax::parse(token);

			if (!value)
				return {};
			
			if (token.type() != TokenType::Semicolon)
			{
				log::parseError(token, "';' after jump statement");
				return {};
			}
		}

		token.increment();

		auto *syntax = new JumpStatementSyntax(token, *type, value);

		return syntax;
	}
}
