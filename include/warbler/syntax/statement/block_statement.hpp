#ifndef WARBLER_SYNTAX_STATEMENT_COMPOUND_STATEMENT
#define WARBLER_SYNTAX_STATEMENT_COMPOUND_STATEMENT

#include <warbler/util/array.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/syntax/statement/statement.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::syntax
{
	class BlockStatement : public Statement
	{
	private:

		Array<Ptr<Statement>> _statements;

	public:

		BlockStatement(Array<Ptr<Statement>>&& statements);

		static Result<BlockStatement> parse(lexicon::Token& token);

		bool validate(semantics::Context& context);
	};
}

#endif
