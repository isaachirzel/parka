#include "parka/ast/statement/statement.hpp"
#include "parka/ast/statement/declaration.hpp"
#include "parka/ast/statement/jump.hpp"

#include "parka/util/print.hpp"

Optional<Box<Statement>> Statement::parse(Token& token)
{
	switch (token.type())
	{
		case TokenType::KeywordVar:
		{
			Declaration declaration;

			if (!parseDeclaration(&declaration, token))
				return false;

			*makeNew(out->declaration) = declaration;
			out->type = STATEMENT_DECLARATION;

			return true;
		}

		case TokenType::KeywordReturn:
		case TokenType::KeywordBreak:
		case TokenType::KeywordContinue:
		case TokenType::KeywordYield:
		{
			JumpStatement jump;

			if (!parseJumpStatement(&jump, token))
				return false;

			*makeNew(out->jump) = jump;
			out->type = STATEMENT_JUMP;

			return true;
		}

		default:
			break;
	}

	Expression expression;

	if (!parseExpression(&expression, token))
		return false;

	if (token.type() != TokenType::Semicolon)
	{
		printParseError(token, "';' after expression statement", NULL);
		return false;
	}

	token.increment();

	*makeNew(out->expression) = expression;
	out->type = STATEMENT_EXPRESSION;

	return true;
}

bool validateStatement(Statement *node, SymbolTable& localTable)
{
	printFmt("Statement type: %d", node->type);

	switch (node->type)
	{
		case STATEMENT_EXPRESSION:
			return validateExpression(node->expression, localTable);

		case STATEMENT_DECLARATION:
			return validateDeclaration(node->declaration, localTable);

		case STATEMENT_JUMP:
			return validateJumpStatement(node->jump, localTable);

		default:
			break;
	}

	exitWithErrorFmt("Unable to validate Statement with StatementType: %d", node->type);
}
