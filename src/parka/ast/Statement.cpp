#include "parka/ast/DeclarationStatement.hpp"
#include "parka/ast/ExpressionStatement.hpp"
#include "parka/ast/JumpStatement.hpp"
#include "parka/ast/Keyword.hpp"

namespace parka::ast
{
	StatementAst *StatementAst::parse(Token& token)
	{
		auto keywordType = KeywordAst::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Var:
				return DeclarationStatementAst::parse(token);

			case KeywordType::Return:
			case KeywordType::Break:
			case KeywordType::Continue:
			case KeywordType::Yield:
				return JumpStatementAst::parse(token);

			default:
				break;
		}

		return ExpressionStatementAst::parse(token);
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