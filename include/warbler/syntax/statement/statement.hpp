#ifndef WARBLER_SYNTAX_STATEMENT_HPP
#define WARBLER_SYNTAX_STATEMENT_HPP

#include <warbler/util/result.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::syntax
{
	class AssignmentStatement;
	class ExpressionStatement;
	class BlockStatement;
	class VariableStatement;
	class IfStatement;

	enum class StatementType
	{
		Assignment,
		Expression,
		Block,
		Variable,
		If
	};
	
	class Statement
	{
		union
		{
			AssignmentStatement *_assignment;
			ExpressionStatement *_expression;
			BlockStatement *_block;
			VariableStatement *_variable;
			IfStatement *_if;
		};

		StatementType _type;

	public:

		Statement(AssignmentStatement&&);
		Statement(ExpressionStatement&&);
		Statement(BlockStatement&&);
		Statement(VariableStatement&&);
		Statement(IfStatement&&);
		Statement(Statement&&);
		Statement(const Statement&) = delete;
		~Statement();
		
		static Result<Statement> parse(lexicon::Token& token);
	};
}

#endif
