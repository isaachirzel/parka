#include "parka/ast/expression/literal/literal.hpp"
#include "parka/ast/expression/literal/bool.hpp"
#include "parka/ast/expression/literal/char.hpp"
#include "parka/ast/expression/literal/float.hpp"
#include "parka/ast/expression/literal/integer.hpp"
#include "parka/ast/expression/literal/string.hpp"
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

		case TokenType::KeywordTrue:
		case TokenType::KeywordFalse:
			return BoolLiteral::parse(token);

		default:
			printParseError(token, "literal");
			return {};
	}
}
