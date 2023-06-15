#ifndef PARKA_SYNTAX_BLOCK_SYNTAX_HPP
#define PARKA_SYNTAX_BLOCK_SYNTAX_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"

namespace parka
{
	class BlockExpressionSyntax : public ExpressionSyntax, public SymbolTable
	{
		Array<StatementSyntax*> _statements;
		SymbolTable *_parent;
		Array<EntityEntry*> *_symbols;
		usize _baseIndex;

	public:

		BlockExpressionSyntax(Array<StatementSyntax*>&& statements);
		BlockExpressionSyntax(BlockExpressionSyntax&&) = default;
		BlockExpressionSyntax(const BlockExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		bool declare(EntitySyntax& entity);
		EntityEntry *find(const Identifier& identifier);
		EntityContext *resolve(const QualifiedIdentifier& identifier);

		SymbolTableType symbolTableType() const { return SymbolTableType::Block; };
		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};

	class BlockExpressionContext : public ExpressionContext
	{
		Array<StatementContext*> _statements;
		ValueType _valueType;

	public:

		BlockExpressionContext(Array<StatementContext*>&& statements, ValueType&& valueType);
		BlockExpressionContext(BlockExpressionContext&&) = default;
		BlockExpressionContext(const BlockExpressionContext&) = delete;

		const ValueType& valueType() const { return _valueType; }
		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};
}

#endif
