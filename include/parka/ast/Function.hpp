#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/ir/Function.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Prototype.hpp"

namespace parka::ast
{
	class PackageAst;

	class FunctionAst : public EntityAst, public SymbolTable
	{
		Snippet _snippet;
		PrototypeAst _prototype;
		ExpressionAst& _body;
		// Symbol table data
		PackageAst *_parent;
		Array<SymbolTableEntry*> _symbols;

	public:

		FunctionAst(PrototypeAst&& prototype, ExpressionAst& body) :
		_snippet(prototype.snippet() + body.snippet()),
		_prototype(std::move(prototype)),
		_body(body),
		_parent(nullptr),
		_symbols()
		{}
		FunctionAst(FunctionAst&&) = default;
		FunctionAst(const FunctionAst&) = delete;

		static FunctionAst *parse(Token& token);
		ir::FunctionIr *validate();
		ir::EntityIr *context() { return validate(); }

		bool declare(EntityAst& entity);
		bool declareSelf(PackageAst& parent);
		SymbolTableEntry *find(const Identifier& identifier);
		ir::EntityIr *resolve(const QualifiedIdentifier& identifier);
		String getSymbol() const;

		SymbolTableType symbolTableType() const { return SymbolTableType::Function; }
		EntityType entityType() const { return EntityType::Function; }
		const Snippet& snippet() const { return _snippet; }
		const String& name() const { return _prototype.identifier().text(); }
		const Identifier& identifier() const { return _prototype.identifier(); }
		
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }

		friend std::ostream& operator<<(std::ostream& out, const FunctionAst& syntax);

		friend class BlockExpressionAst;
	};
}

#endif
