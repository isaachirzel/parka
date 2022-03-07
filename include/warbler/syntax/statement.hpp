#ifndef WARBLER_SYNTAX_STATEMENT_HPP
#define WARBLER_SYNTAX_STATEMENT_HPP

namespace warbler::syntax
{
	enum StatementType
	{
		Block,
		Declaration,
		Expression
	};

	struct Statement
	{
		virtual StatementType type() const = 0;
	};

	struct BlockStatement : public Statement
	{
	};

	struct DeclarationStatement : public Statement
	{
		
	};
};

#endif
