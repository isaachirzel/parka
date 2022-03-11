#ifndef WARBLER_SYNTAX_STATEMENT_DECLARATION_STATEMENT_HPP
#define WARBLER_SYNTAX_STATEMENT_DECLARATION_STATEMENT_HPP

// local headers
#include <warbler/syntax/statement/declaration.hpp>
#include <warbler/syntax/expression/conditional_expression.hpp>
#include <warbler/syntax/statement/statement.hpp>

namespace warbler::syntax
{
	class VariableStatement : public Statement
	{
	private:

		Variable _declaration;
		Expression _value;

	public:

		VariableStatement(Variable&& declaration, Expression&& value);
		VariableStatement(VariableStatement&&) = default;
		VariableStatement(const VariableStatement&) = delete;

		static Result<VariableStatement> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
	};
}

#endif
