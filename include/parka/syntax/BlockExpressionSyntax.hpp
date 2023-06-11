#ifndef PARKA_SYNTAX_BLOCK_SYNTAX_HPP
#define PARKA_SYNTAX_BLOCK_SYNTAX_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	class BlockExpressionSyntax : public ExpressionSyntax
	{
		Array<StatementSyntax*> _statements;

	public:

		BlockExpressionSyntax(Array<StatementSyntax*>&& statements) :
		_statements(std::move(statements))
		{}
		BlockExpressionSyntax(BlockExpressionSyntax&&) = default;
		BlockExpressionSyntax(const BlockExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable) const;

		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};
}

#endif
