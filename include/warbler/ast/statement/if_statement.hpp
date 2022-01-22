#ifndef WARBLER_AST_STATEMENT_SELECTION_STATEMENT_HPP
#define WARBLER_AST_STATEMENT_SELECTION_STATEMENT_HPP

// local headers
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/util/array.hpp>

namespace warbler::ast
{
	class Statement;

	enum IfType
	{
		IF_THEN,
		IF_THEN_ELSE,
		IF_THEN_ELSE_IF
	};

	class IfStatement
	{
	private:

		Expression _condition;
		Array<Statement> _then_body;

		union
		{
			Array<Statement> _else_body;
			IfStatement *_else_if;
		};

		IfType _type;

	public:

		IfStatement(Expression&& condition, Array<Statement>&& then_body);
		IfStatement(Expression&& condition, Array<Statement>&& then_body, Array<Statement>&& else_body);
		IfStatement(Expression&& condition, Array<Statement>&& then_body, IfStatement *else_if);
		IfStatement(IfStatement&& other);
		IfStatement(const IfStatement& other);
		~IfStatement();

		static Result<IfStatement> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
		
		IfStatement operator=(IfStatement&& other);
		IfStatement operator=(const IfStatement& other);
	};
}

#endif
