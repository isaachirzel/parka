#include "parka/log/Log.hpp"
#include "parka/repository/StatementSyntaxId.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/syntax/JumpStatementSyntax.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream&, const StatementSyntaxId&)
	{
		log::notImplemented(here());
	}

	bool StatementSyntaxId::operator==(const StatementSyntaxId& other) const
	{
		return _type == other._type && _index == other._index;
	}

	// const StatementSyntax& StatementSyntaxId::operator*() const
	// {
	// 	switch (_type)
	// 	{
	// 		case StatementType::Declaration:
	// 			return declarationStatements[_index];

	// 		case StatementType::Expression:
	// 			return expressionStatements[_index];

	// 		case StatementType::Jump:
	// 			return jumpStatements[_index];

	// 		default:
	// 			break;
	// 	}

	// 	log::fatal("Unable to get Statement of type: $", (int)_type);
	// }

	// const StatementSyntax *StatementSyntaxId::operator->() const
	// {
	// 	return &(*(*this));
	// }
}
