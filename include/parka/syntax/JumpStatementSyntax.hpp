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
		const ExpressionSyntax *_value;
		JumpType _type;

		JumpStatementSyntax(const Token& token, JumpType type, const ExpressionSyntax *value) :
		_token(token),
		_value(value),
		_type(type)
		{}

	public:

		JumpStatementSyntax(JumpStatementSyntax&&) = default;
		JumpStatementSyntax(const JumpStatementSyntax&) = delete;

		static const StatementSyntax *parse(Token& token);

		StatementType statementType() const { return StatementType::Jump; }
		const auto& token() const { return _token; }
		bool hasValue() const { return !!_value; }
		const auto& value() const { assert(_value != nullptr); return *_value; }
		const auto& type() const { return _type; }
	};
}

#endif
