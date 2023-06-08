#ifndef PARKA_SYNTAX_BLOCK_SYNTAX_HPP
#define PARKA_SYNTAX_BLOCK_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	class BlockSyntax : public ExpressionSyntax
	{
		Array<const StatementSyntax*> _statements;

		BlockSyntax(Array<const StatementSyntax*>&& statements) :
		_statements(std::move(statements))
		{}

	public:

		BlockSyntax(BlockSyntax&&) = default;
		BlockSyntax(const BlockSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};
}

#endif
