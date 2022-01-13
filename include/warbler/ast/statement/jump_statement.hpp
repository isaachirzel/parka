#ifndef WARBLER_AST_JUMP_STATEMENT_HPP
#define WARBLER_AST_JUMP_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler
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
