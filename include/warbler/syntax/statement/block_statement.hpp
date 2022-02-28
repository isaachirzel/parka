#ifndef WARBLER_SYNTAX_STATEMENT_COMPOUND_STATEMENT
#define WARBLER_SYNTAX_STATEMENT_COMPOUND_STATEMENT

#include <warbler/util/array.hpp>
#include <warbler/syntax/statement/statement.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::syntax
{
	class BlockStatement : public Statement
	{
	private:

		semantics::BlockContext _context;
		Array<Ptr<Statement>> _statements;

	public:

		BlockStatement(Array<Ptr<Statement>>&& statements);

		static Result<BlockStatement> parse(lexicon::TokenIterator& iter);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
