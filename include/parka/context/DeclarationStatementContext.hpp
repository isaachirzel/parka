#ifndef PARKA_CONTEXT_DECLARATION_STATEMENT_CONTEXT_HPP
#define PARKA_CONTEXT_DECLARATION_STATEMENT_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/context/StatementContext.hpp"
#include "parka/context/VariableContext.hpp"

namespace parka
{
	class DeclarationStatementContext : public StatementContext
	{
		VariableContext& _variable;
		ExpressionContext& _value;

	public:

		DeclarationStatementContext(VariableContext& variable, ExpressionContext& value);
		DeclarationStatementContext(DeclarationStatementContext&&) = default;
		DeclarationStatementContext(const DeclarationStatementContext&) = delete;

		StatementType statementType() const { return StatementType::Declaration; }
	};
}

#endif
