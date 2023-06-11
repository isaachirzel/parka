#ifndef PARKA_SYNTAX_STATEMENT_JUMP_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_JUMP_SYNTAX_HPP

#include "parka/enum/JumpType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class JumpStatementSyntax : public StatementSyntax
	{
		Token _token;
		ExpressionSyntax *_value;
		JumpType _type;

	public:

		JumpStatementSyntax(const Token& token, JumpType type, ExpressionSyntax *value) :
		_token(token),
		_value(value),
		_type(type)
		{}
		JumpStatementSyntax(JumpStatementSyntax&&) = default;
		JumpStatementSyntax(const JumpStatementSyntax&) = delete;

		static StatementSyntax *parse(Token& token);

		StatementType statementType() const { return StatementType::Jump; }
		const auto& token() const { return _token; }
		bool hasValue() const { return !!_value; }
		const auto& value() const { assert(_value != nullptr); return *_value; }
		const auto& type() const { return _type; }
	};
}

#endif
