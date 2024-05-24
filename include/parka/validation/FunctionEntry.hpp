#ifndef PARKA_VALIDATION_FUNCTION_ENTRY_HPP
#define PARKA_VALIDATION_FUNCTION_ENTRY_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/validation/FunctionSymbolTable.hpp"
#include "parka/validation/Resolvable.hpp"
#include "parka/validation/SymbolTable.hpp"

namespace parka::validation
{
	class FunctionEntry: public Resolvable
	{
		const ast::FunctionAst& _ast;
		FunctionSymbolTable _symbolTable;
		ir::FunctionIr *_ir;
		bool _isValidated;

	public:

		FunctionEntry(const ast::FunctionAst& ast, SymbolTable& symbolTable);
		FunctionEntry(FunctionEntry&&) = default;
		FunctionEntry(const FunctionEntry&) = delete;

		ir::FunctionIr* resolve();

		FunctionSymbolTable* symbolTable() { return &_symbolTable; }
		const auto& ast() const { return _ast; }
		const ast::IdentifierAst& identifier() const { return _ast.prototype().identifier(); }
		const String& name() const { return _ast.prototype().identifier().text(); }
	};
}

#endif
