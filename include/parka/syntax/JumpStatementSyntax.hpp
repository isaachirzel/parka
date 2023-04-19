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
		Optional<ExpressionSyntaxId> _value;
		JumpType _type;

		JumpStatementSyntax(const Token& token, JumpType type, Optional<ExpressionSyntaxId>&& value) :
		_token(token),
		_value(std::move(value)),
		_type(type)
		{}

	public:

		JumpStatementSyntax(JumpStatementSyntax&&) = default;
		JumpStatementSyntax(const JumpStatementSyntax&) = delete;

		static Optional<StatementSyntaxId> parse(Token& token);

		const auto& token() const { return _token; }
		bool hasValue() const { return _value; }
		const auto& value() const { return _value; }
		const auto& type() const { return _type; }
	};
}

#endif
