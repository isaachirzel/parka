#ifndef PARKA_VALIDATOR_FUNCTION_VALIDATOR_HPP
#define PARKA_VALIDATOR_FUNCTION_VALIDATOR_HPP

#include "parka/ast/Function.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ir/Function.hpp"
#include "parka/ir/Prototype.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/symbol/ParameterEntry.hpp"

namespace parka::validator
{
	class FunctionSymbolTable: public SymbolTable, public Resolvable
	{
		const ast::FunctionAst& _ast;
		String _symbol;
		Array<Resolvable*> _symbols;
		Array<VariableEntry> _variables;
		Array<ParameterEntry> _parameters;
		SymbolTable *_parent;
		ir::FunctionIr *_ir;

	public:

		FunctionSymbolTable(const ast::FunctionAst& ast, SymbolTable *parent = nullptr);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		bool declare(const Declarable& declarable);
		Resolvable *find(const ast::Identifier& identifier);
		Resolution *resolve(const ast::QualifiedIdentifier& identifier);

		auto& ast() { return _ast; }
		const String& symbol() const { return _symbol; }
		const String& name() const { return _ast.identifier().text(); }

		friend std::ostream& operator<<(std::ostream& out, const FunctionSymbolTable& syntax);
	};
}

#endif
