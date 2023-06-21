#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/enum/DeclarableType.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/ir/Function.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Prototype.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka::ast
{
	class PackageAst;

	class FunctionAst : public Declarable, public SymbolTable
	{
		Snippet _snippet;
		PrototypeAst _prototype;
		ExpressionAst& _body;
		// Symbol table data
		PackageAst *_parent;
		Array<Resolvable*> _symbols;

	public:

		FunctionAst(PrototypeAst&& prototype, ExpressionAst& body) :
		Declarable(DeclarableType::Function, ResolvableType::Function),
		SymbolTable(SymbolTableType::Function),
		_snippet(prototype.snippet() + body.snippet()),
		_prototype(std::move(prototype)),
		_body(body),
		_parent(nullptr),
		_symbols()
		{}
		FunctionAst(FunctionAst&&) = default;
		FunctionAst(const FunctionAst&) = delete;

		static FunctionAst *parse(Token& token);

		bool declare(Declarable& declarable);
		bool declareSelf(PackageAst& parent);
		Resolvable *find(const Identifier& identifier);
		Resolution *resolve(const QualifiedIdentifier& identifier);
		String getSymbol() const;

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
