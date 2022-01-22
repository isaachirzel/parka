#ifndef WARBLER_AST_STATEMENT_HPP
#define WARBLER_AST_STATEMENT_HPP

#include <warbler/ast/statement/expression_statement.hpp>
#include <warbler/ast/statement/declaration_statement.hpp>
#include <warbler/ast/statement/if_statement.hpp>
//#include <warbler/ast/statement/loop_statement.hpp>
//#include <warbler/ast/statement/jump_statement.hpp>

namespace warbler::ast
{
	enum StatementType
	{
		STATEMENT_EXPRESSION,
		STATEMENT_DECLARATION,		
		STATEMENT_IF_THEN,
		// STATEMENT_LOOP,
		// STATEMENT_JUMP
	};

	class Statement
	{
	private:

		union
		{
			ExpressionStatement _expression;
			DeclarationStatement _declaration;
			IfStatement _if_then;
			//LoopStatement _loop;
			//JumpStatement _jump;
		};

		StatementType _type;

	public:

		Statement(ExpressionStatement&& expression);
		Statement(DeclarationStatement&& declaration);
		Statement(IfStatement&& if_then);
		//Statement(LoopStatement&& loop);
		//Statement(JumpStatement&& jump);
		Statement(Statement&& other);
		Statement(const Statement& other);
		~Statement();

		static Result<Statement> parse(TokenIterator& iter);
		static Result<Array<Statement>> parse_compound(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;

		Statement& operator=(Statement&& other);
		Statement& operator=(const Statement& other);
	};
}

#endif
