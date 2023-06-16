#ifndef PARKA_SYNTAX_STATEMENT_JUMP_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_JUMP_SYNTAX_HPP

#include "parka/enum/JumpType.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class JumpStatementSyntax : public StatementSyntax
	{
		Snippet _snippet;
		ExpressionSyntax *_value;
		JumpType _type;

	public:

		JumpStatementSyntax(const Snippet& snippet, JumpType type, ExpressionSyntax *value) :
		_snippet(snippet),
		_value(value),
		_type(type)
		{}
		JumpStatementSyntax(JumpStatementSyntax&&) = default;
		JumpStatementSyntax(const JumpStatementSyntax&) = delete;

		static StatementSyntax *parse(Token& token);
		StatementContext *validate(SymbolTable& symbolTable);

		StatementType statementType() const { return StatementType::Jump; }
		const Snippet& snippet() const { return _snippet; }

		bool hasValue() const { return !!_value; }
		const auto& value() const { assert(_value != nullptr); return *_value; }
		const auto& type() const { return _type; }
	};
}

#endif
