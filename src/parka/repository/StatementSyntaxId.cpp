// #include "parka/log/Log.hpp"
// #include "parka/repository/StatementAstId.hpp"
// #include "parka/ast/Statement.hpp"
// #include "parka/ast/DeclarationStatement.hpp"
// #include "parka/ast/ExpressionStatement.hpp"
// #include "parka/ast/JumpStatement.hpp"
// #include "parka/util/Pool.hpp"
// #include "parka/util/Print.hpp"

// namespace parka
// {
// 	std::ostream& operator<<(std::ostream&, const StatementAstId&)
// 	{
// 		log::notImplemented(here());
// 	}

// 	bool StatementAstId::operator==(const StatementAstId& other) const
// 	{
// 		return _type == other._type && _index == other._index;
// 	}

// 	// const StatementAst& StatementAstId::operator*() const
// 	// {
// 	// 	switch (_type)
// 	// 	{
// 	// 		case StatementType::Declaration:
// 	// 			return declarationStatements[_index];

// 	// 		case StatementType::Expression:
// 	// 			return expressionStatements[_index];

// 	// 		case StatementType::Jump:
// 	// 			return jumpStatements[_index];

// 	// 		default:
// 	// 			break;
// 	// 	}

// 	// 	log::fatal("Unable to get Statement of type: $", (int)_type);
// 	// }

// 	// const StatementAst *StatementAstId::operator->() const
// 	// {
// 	// 	return &(*(*this));
// 	// }
// }
