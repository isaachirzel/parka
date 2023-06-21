#ifndef PARKA_AST_BLOCK_HPP
#define PARKA_AST_BLOCK_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include <exception>

// TODO: Make block a statement

namespace parka::ast
{
	class BlockExpressionAst : public ExpressionAst, public SymbolTable
	{
		Snippet _snippet;
		Array<StatementAst*> _statements;

		SymbolTable *_parent;
		Array<Resolvable*> *_symbols;
		usize _baseIndex;

	public:

		BlockExpressionAst(const Snippet& snippet, Array<StatementAst*>&& statements) :
		ExpressionAst(ExpressionType::Block),
		SymbolTable(SymbolTableType::Block),
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

		bool declare(Declarable& declarable);
		Resolvable *find(const Identifier& identifier);
		ir::EntityIr *resolve(const QualifiedIdentifier& identifier);

		const Snippet &snippet() const { return _snippet; }
		const auto& statements() const { return _statements; }
	};

}

#endif
