#include "parka/ast/DeclarationStatement.hpp"
#include "parka/ast/ExpressionStatement.hpp"
#include "parka/ast/JumpStatement.hpp"
#include "parka/ast/Keyword.hpp"

namespace parka
{
	StatementSyntax *StatementSyntax::parse(Token& token)
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

	std::ostream& operator<<(std::ostream& out, const StatementType& type)
	{
		switch (type)
		{
			case StatementType::Declaration:
				out << "declaration";
				break;

			case StatementType::Expression:
				out << "expression";
				break;

			case StatementType::Jump:
				out << "jump";
				break;

			default:
				out << '(' << (int)type << ") Invalid";
		}

		return out;
	}
}