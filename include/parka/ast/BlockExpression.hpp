#ifndef PARKA_AST_BLOCK_HPP
#define PARKA_AST_BLOCK_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include <exception>

// TODO: Make block a statement

namespace parka::ast
{
	class BlockExpressionAst : public ExpressionAst, public SymbolTable
	{
		Snippet _snippet;
		Array<StatementAst*> _statements;

		SymbolTable *_parent;
		Array<SymbolTableEntry*> *_symbols;
		usize _baseIndex;

	public:

		BlockExpressionAst(const Snippet& snippet, Array<StatementAst*>&& statements) :
		_snippet(snippet),
		_statements(std::move(statements)),
		_parent(nullptr),
		_symbols(nullptr),
		_baseIndex(0)
		{}
		BlockExpressionAst(BlockExpressionAst&&) = default;
		BlockExpressionAst(const BlockExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		bool declare(EntityAst& entity);
		SymbolTableEntry *find(const Identifier& identifier);
		ir::EntityIr *resolve(const QualifiedIdentifier& identifier);

		SymbolTableType symbolTableType() const { return SymbolTableType::Block; };
		ExpressionType expressionType() const { return ExpressionType::Block; }
		const Snippet &snippet() const { return _snippet; }
		const auto& statements() const { return _statements; }
	};

}

#endif
