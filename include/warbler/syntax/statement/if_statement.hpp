#ifndef WARBLER_SYNTAX_STATEMENT_SELECTION_STATEMENT_HPP
#define WARBLER_SYNTAX_STATEMENT_SELECTION_STATEMENT_HPP

// local headers
#include <warbler/syntax/statement/block_statement.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/expression/conditional_expression.hpp>
#include <warbler/util/array.hpp>

namespace warbler::syntax
{
	enum class IfType
	{
		Then,
		ThenElse,
		ThenElseIf
	};

	class IfStatement : public Statement
	{
	private:

		Expression _condition;
		BlockStatement _then_body;

		union
		{
			BlockStatement _else_body;
			IfStatement *_else_if;
		};

		IfType _type;

	public:

		IfStatement(Expression&& condition, BlockStatement&& then_body);
		IfStatement(Expression&& condition, BlockStatement&& then_body, BlockStatement&& else_body);
		IfStatement(Expression&& condition, BlockStatement&& then_body, IfStatement *else_if);
		IfStatement(IfStatement&& other);
		IfStatement(const IfStatement& other) = delete;
		~IfStatement();

		static Result<IfStatement> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
		
		IfStatement& operator=(IfStatement&& other);
		IfStatement& operator=(const IfStatement& other) = delete;
	};
}

#endif
