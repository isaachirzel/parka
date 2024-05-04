#ifndef PARKA_AST_STATEMENT_JUMP_HPP
#define PARKA_AST_STATEMENT_JUMP_HPP

#include "parka/enum/JumpType.hpp"
#include "parka/enum/StatementType.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"

namespace parka::ast
{
	class JumpStatementAst: public StatementAst
	{
		Snippet _snippet;
		ExpressionAst *_value;
		JumpType _type;

	public:

		JumpStatementAst(const Snippet& snippet, JumpType type, ExpressionAst *value):
		StatementAst(StatementType::Jump),
		_snippet(snippet),
		_value(value),
		_type(type)
		{}
		JumpStatementAst(JumpStatementAst&&) = default;
		JumpStatementAst(const JumpStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		bool hasValue() const { return !!_value; }
		const auto& value() const { assert(_value != nullptr); return *_value; }
		const auto& jumpType() const { return _type; }
	};
}

#endif
