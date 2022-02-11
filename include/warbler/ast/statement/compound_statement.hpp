#ifndef WARBLER_AST_STATEMENT_COMPOUND_STATEMENT
#define WARBLER_AST_STATEMENT_COMPOUND_STATEMENT

#include <warbler/util/array.hpp>
#include <warbler/ast/statement/statement.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::ast
{
	class CompoundStatement : public Statement
	{
	private:

		Array<Ptr<Statement>> _statements;

	public:

		CompoundStatement(Array<Ptr<Statement>>&& statements);

		static Result<CompoundStatement> parse(TokenIterator& iter);
		
		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
