#include "parka/ast/statement/statement.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/statement/declaration.hpp"
#include "parka/ast/statement/expression.hpp"
#include "parka/ast/statement/jump.hpp"

#include "parka/util/print.hpp"

Optional<StatementId> Statement::parse(Token& token)
{
	auto keywordType = Keyword::getKeywordType(token);

	switch (keywordType)
	{
		case KeywordType::Var:
			return Declaration::parse(token);

		case KeywordType::Return:
		case KeywordType::Break:
		case KeywordType::Continue:
		case KeywordType::Yield:
			return JumpStatement::parse(token);

		default:
			break;
	}

	return ExpressionStatement::parse(token);
}

bool Statement::validate(const EntityId&)
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

	// exitWithError("Unable to validate Statement with StatementType: $", node->type);
}
