#ifndef WARBLER_AST_LOOP_STATEMENT_HPP
#define WARBLER_AST_LOOP_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
#include <warbler/ast/loop_condition.hpp>

namespace warbler
{
	class Statement;
	
	enum LoopType
	{
		LOOP_FOR,
		LOOP_WHILE,
		LOOP_LOOP
	};

	class LoopStatement
	{
	private:

		std::vector<Statement> _body;
		LoopCondition _condition;
		LoopType _type;

	public:

		LoopStatement(std::vector<Statement>&& body, LoopCondition&& condition, LoopType type);

		static Result<LoopStatement> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
