#ifndef PARKA_VALIDATOR_FUNCTION_VALIDATOR_HPP
#define PARKA_VALIDATOR_FUNCTION_VALIDATOR_HPP

#include "parka/ast/Function.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ir/Function.hpp"
#include "parka/ir/Prototype.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"

namespace parka::validator
{
	class FunctionSymbolTable: public SymbolTable, public Resolvable
	{
		const ast::FunctionAst& _ast;
		String _scope;
		Array<Resolvable*> _symbols;
		SymbolTable *_parent;
		ir::FunctionIr *_ir;

	public:

		FunctionSymbolTable(const ast::FunctionAst& ast, SymbolTable *parent = nullptr);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		bool declare(const Declarable& entity);
		// bool declareSelf(astPackageAst& parent);
		Resolvable *find(const ast::Identifier& identifier);
		Resolution *resolve(const ast::QualifiedIdentifier& identifier);

		auto& ast() { return _ast; }
		const String& scope() const { return _scope; }
		const String& name() const { return _ast.identifier().text(); }

		friend std::ostream& operator<<(std::ostream& out, const FunctionSymbolTable& syntax);
	};
}

#endif
