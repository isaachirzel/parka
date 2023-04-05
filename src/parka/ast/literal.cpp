#include "parka/ast/literal.hpp"
#include "parka/ast/bool_literal.hpp"
#include "parka/ast/char_literal.hpp"
#include "parka/ast/float_literal.hpp"
#include "parka/ast/integer_literal.hpp"
#include "parka/ast/string_literal.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> Literal::parse(Token& token)
{
	switch (token.type())
	{
		case TokenType::CharacterLiteral:
			return CharLiteral::parse(token);

		case TokenType::StringLiteral:
			return StringLiteral::parse(token);

		case TokenType::IntegerLiteral:
			return IntegerLiteral::parse(token);

		case TokenType::FloatLiteral:
			return FloatLiteral::parse(token);

		case TokenType::Identifier:
			return BoolLiteral::parse(token);

		default:
			printParseError(token, "literal");
			return {};
	}
}
