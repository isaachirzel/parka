#ifndef WARBLER_SEMANTICS_BLOCK_STATEMENT_HPP
#define WARBLER_SEMANTICS_BLOCK_STATEMENT_HPP

#include <warbler/syntax/statement/block_statement.hpp>
#include <warbler/semantics/statement/statement.hpp>

namespace warbler::semantics
{
	class BlockStatement
	{
		Array<Statement> _statements;

		BlockStatement(Array<Statement>&& statements);

	public:

		static Result<BlockStatement> validate(const syntax::BlockStatement& syntax);
	};
}

#endif
