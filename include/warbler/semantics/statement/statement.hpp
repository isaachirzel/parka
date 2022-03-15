#ifndef WARBLER_SEMANTICS_STATEMENT_HPP
#define WARBLER_SEMANTICS_STATEMENT_HPP

#include <warbler/syntax/statement/statement.hpp>

namespace warbler::semantics
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

	static Result<Statement> validate(const syntax::Statement& syntax);
	};
}

#endif
