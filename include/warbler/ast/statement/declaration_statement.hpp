#ifndef WARBLER_AST_STATEMENT_DECLARATION_STATEMENT_HPP
#define WARBLER_AST_STATEMENT_DECLARATION_STATEMENT_HPP

// local headers
#include <warbler/ast/declaration.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/ast/statement/statement.hpp>

namespace warbler::ast
{
	class DeclarationStatement : public Statement
	{
	private:

		Declaration _declaration;
		Ptr<Expression> _value;

	public:

		DeclarationStatement(Declaration&& declaration, Ptr<Expression>&& value);
		DeclarationStatement(DeclarationStatement&&) = default;
		DeclarationStatement(const DeclarationStatement&) = delete;

		static Result<DeclarationStatement> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
