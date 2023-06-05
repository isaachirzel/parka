#include "parka/log/Log.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/syntax/JumpStatementSyntax.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	static Pool<DeclarationStatementSyntax> declarationStatements(10'000'000);
	static Pool<ExpressionStatementSyntax> expressionStatements(10'000'000);
	static Pool<JumpStatementSyntax> jumpStatements(1'000'000);

	StatementSyntaxId StatementSyntaxId::create(DeclarationStatementSyntax&& value)
	{
		auto index = declarationStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::Declaration, index);
	}

	StatementSyntaxId StatementSyntaxId::create(ExpressionStatementSyntax&& value)
	{
		auto index = expressionStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::Expression, index);
	}

	StatementSyntaxId StatementSyntaxId::create(JumpStatementSyntax&& value)
	{
		auto index = jumpStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::Jump, index);
	}

	std::ostream& operator<<(std::ostream&, const ExpressionSyntaxId&)
	{
		log::notImplemented(here());
	}

	bool ExpressionSyntaxId::operator==(const ExpressionSyntaxId& other) const
	{
		return _type == other._type && _index == other._index;
	}

	const StatementSyntax& StatementSyntaxId::operator*() const
	{
		switch (_type)
		{
			case StatementType::Declaration:
				return declarationStatements[_index];

			case StatementType::Expression:
				return expressionStatements[_index];

			case StatementType::Jump:
				return jumpStatements[_index];

			default:
				break;
		}

		log::fatal("Unable to get Statement of type: $", (int)_type);
	}

	const StatementSyntax *StatementSyntaxId::operator->() const
	{
		return &(*(*this));
	}
}
