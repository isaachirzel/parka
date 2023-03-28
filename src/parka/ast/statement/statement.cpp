#include "parka/ast/statement/statement.hpp"
#include "parka/ast/statement/declaration.hpp"
#include "parka/ast/statement/expression.hpp"
#include "parka/ast/statement/jump.hpp"

#include "parka/util/print.hpp"

Optional<StatementId> Statement::parse(Token& token)
{
	switch (token.type())
	{
		case TokenType::KeywordVar:
			return Declaration::parse(token);

		case TokenType::KeywordReturn:
		case TokenType::KeywordBreak:
		case TokenType::KeywordContinue:
		case TokenType::KeywordYield:
			return JumpStatement::parse(token);

		default:
			break;
	}

	return ExpressionStatement::parse(token);
}

bool Statement::validate(SymbolTable& symbols)
{
	exitNotImplemented(here());

	// switch (node->type)
	// {
	// 	case STATEMENT_EXPRESSION:
	// 		return validateExpression(node->expression, symbols);

	// 	case STATEMENT_DECLARATION:
	// 		return validateDeclaration(node->declaration, symbols);

	// 	case STATEMENT_JUMP:
	// 		return validateJumpStatement(node->jump, symbols);

	// 	default:
	// 		break;
	// }

	// exitWithError("Unable to validate Statement with StatementType: %d", node->type);
}
