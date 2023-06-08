#include "parka/syntax/StatementSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/syntax/JumpStatementSyntax.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	static Pool<DeclarationStatementSyntax> declarationStatements(10'000'000);
	static Pool<ExpressionStatementSyntax> expressionStatements(10'000'000);
	static Pool<JumpStatementSyntax> jumpStatements(1'000'000);

	const StatementSyntax& StatementSyntax::create(StatementSyntax&& syntax)
	{
		auto type = syntax.statementType();

		switch (type)
		{
			case StatementType::Declaration:
				return declarationStatements.add(std::move((DeclarationStatementSyntax&)syntax));

			case StatementType::Expression:
				return expressionStatements.add(std::move((ExpressionStatementSyntax&)syntax));

			case StatementType::Jump:
				return jumpStatements.add(std::move((JumpStatementSyntax&)syntax));

			default:
				break;
		}
		

		log::fatal("Unable to create StatementSyntax with type: $", type);
	}

	const StatementSyntax *StatementSyntax::parse(Token& token)
	{
		auto keywordType = KeywordSyntax::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Var:
				return DeclarationStatementSyntax::parse(token);

			case KeywordType::Return:
			case KeywordType::Break:
			case KeywordType::Continue:
			case KeywordType::Yield:
				return JumpStatementSyntax::parse(token);

			default:
				break;
		}

		return ExpressionStatementSyntax::parse(token);
	}
}
