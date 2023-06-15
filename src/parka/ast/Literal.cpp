#include "parka/ast/Literal.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BoolLiteral.hpp"
#include "parka/ast/CharLiteral.hpp"
#include "parka/ast/FloatLiteral.hpp"
#include "parka/ast/IntegerLiteral.hpp"
#include "parka/ast/StringLiteral.hpp"
#include "parka/util/Print.hpp"

namespace parka::LiteralSyntax
{
	ExpressionSyntax *parse(Token& token)
	{
		switch (token.type())
		{
			case TokenType::CharacterLiteral:
				return CharLiteralSyntax::parse(token);

			case TokenType::StringLiteralSyntax:
				return StringLiteralSyntax::parse(token);

			case TokenType::IntegerLiteralSyntax:
				return IntegerLiteralSyntax::parse(token);

			case TokenType::FloatLiteralSyntax:
				return FloatLiteralSyntax::parse(token);

			case TokenType::Identifier:
				return BoolLiteralSyntax::parse(token);

			default:
				break;
		}
		
		log::parseError(token, "literal");
		
		return {};
	}
}
