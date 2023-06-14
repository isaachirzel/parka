#include "parka/context/DeclarationStatementContext.hpp"

namespace parka
{
	DeclarationStatementContext::DeclarationStatementContext(VariableContext& variable, ExpressionContext& value) :
	_variable(variable),
	_value(value)
	{}
}
