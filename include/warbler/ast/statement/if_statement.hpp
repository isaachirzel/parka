#ifndef WARBLER_AST_STATEMENT_SELECTION_STATEMENT_HPP
#define WARBLER_AST_STATEMENT_SELECTION_STATEMENT_HPP

// local headers
#include <warbler/ast/statement/compound_statement.hpp>
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/util/array.hpp>

namespace warbler::ast
{
	enum IfType
	{
		IF_THEN,
		IF_THEN_ELSE,
		IF_THEN_ELSE_IF
	};

	class IfStatement : public Statement
	{
	private:

		Ptr<Expression> _condition;
		CompoundStatement _then_body;

		union
		{
			CompoundStatement _else_body;
			IfStatement *_else_if;
		};

		IfType _type;

	public:

		IfStatement(Ptr<Expression>&& condition, CompoundStatement&& then_body);
		IfStatement(Ptr<Expression>&& condition, CompoundStatement&& then_body, CompoundStatement&& else_body);
		IfStatement(Ptr<Expression>&& condition, CompoundStatement&& then_body, IfStatement *else_if);
		IfStatement(IfStatement&& other);
		IfStatement(const IfStatement& other) = delete;
		~IfStatement();

		static Result<IfStatement> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		
		IfStatement& operator=(IfStatement&& other);
		IfStatement& operator=(const IfStatement& other) = delete;
	};
}

#endif
