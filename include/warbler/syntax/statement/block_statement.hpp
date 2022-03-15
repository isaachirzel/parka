#ifndef WARBLER_SYNTAX_STATEMENT_COMPOUND_STATEMENT
#define WARBLER_SYNTAX_STATEMENT_COMPOUND_STATEMENT

#include <warbler/util/array.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/syntax/statement/statement.hpp>

namespace warbler::syntax
{
	class BlockStatement
	{
	private:

		Array<Statement> _statements;

	public:

		BlockStatement(Array<Statement>&& statements);

		static Result<BlockStatement> parse(lexicon::Token& token);

		
	};
}

#endif
