#ifndef WARBLER_SYNTAX_JUMP_STATEMENT_HPP
#define WARBLER_SYNTAX_JUMP_STATEMENT_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/result.hpp>
#include <warbler/syntax//expression/expression.hpp>

namespace warbler::syntax
{
	enum JumpType
	{
		JUMP_CONTINUE,
		JUMP_BREAK,
		JUMP_RETURN,
		JUMP_EMIT
	};

	class JumpStatement
	{
	private:
		
		Expression *_value;
		JumpType _type;

	public:

		JumpStatement(Expression *value, JumpType type);

		static Result<JumpStatement> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
