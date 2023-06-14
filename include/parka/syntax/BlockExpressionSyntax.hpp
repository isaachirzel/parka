#ifndef PARKA_SYNTAX_BLOCK_SYNTAX_HPP
#define PARKA_SYNTAX_BLOCK_SYNTAX_HPP

#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"

namespace parka
{
	class BlockExpressionSyntax : public ExpressionSyntax, public SymbolTable
	{
		Array<StatementSyntax*> _statements;

		SymbolTable *_parent;
		Array<EntitySyntax*> *_symbols;
		usize _baseIndex;

	private:

		bool declareEntity(EntitySyntax& entity);

	public:

		BlockExpressionSyntax(Array<StatementSyntax*>&& statements);
		BlockExpressionSyntax(BlockExpressionSyntax&&) = default;
		BlockExpressionSyntax(const BlockExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		bool declare(EntitySyntax& entity);
		EntitySyntax *resolve(const Identifier& identifier);
		EntitySyntax *resolve(const QualifiedIdentifier& identifier);

		SymbolTable *parent() { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Block; };
		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};
}

#endif
