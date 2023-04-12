#ifndef PARKA_SYNTAX_BLOCK_SYNTAX_HPP
#define PARKA_SYNTAX_BLOCK_SYNTAX_HPP

#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/type/Type.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	class BlockSyntax : public ExpressionSyntax
	{
		Array<StatementSyntaxId> _statements;

		BlockSyntax(Array<StatementSyntaxId>&& statements) :
		_statements(std::move(statements))
		{}

	public:

		BlockSyntax(BlockSyntax&&) = default;
		BlockSyntax(const BlockSyntax&) = delete;
		~BlockSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& statements() const { return _statements; }
	};
}

#endif
