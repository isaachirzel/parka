#ifndef PARKA_SYNTAX_BLOCK_SYNTAX_HPP
#define PARKA_SYNTAX_BLOCK_SYNTAX_HPP

#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/type/Type.hpp"
#include "parka/util/Primitives.hpp"

namespace parka
{
	class BlockSyntax : public ExpressionSyntax
	{
		Array<StatementId> _statements;

		BlockSyntax(Array<StatementId>&& statements) :
		_statements(std::move(statements))
		{}

	public:

		BlockSyntax(BlockSyntax&&) = default;
		BlockSyntax(const BlockSyntax&) = delete;
		~BlockSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& statements() const { return _statements; }
	};
}

#endif
