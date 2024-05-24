#ifndef PARKA_VALIDATION_VARIABLE_ENTRY_HPP
#define PARKA_VALIDATION_VARIABLE_ENTRY_HPP

#include "parka/ast/VariableAst.hpp"
#include "parka/ir/VariableIr.hpp"
#include "parka/validation/Resolvable.hpp"

namespace parka::validation
{
	class VariableEntry: public Resolvable
	{
		const ast::VariableAst& _ast;
		ir::VariableIr *_ir;

	public:

		VariableEntry(const ast::VariableAst& ast, ir::VariableIr *ir);
		VariableEntry(VariableEntry&&) = default;
		VariableEntry(const VariableEntry&) = delete;

		ir::VariableIr *resolve();

		SymbolTable* symbolTable() { return nullptr; }
		const auto& ast() const { return _ast; }
		const ast::IdentifierAst& identifier() const { return _ast.identifier(); }
		const String& name() const { return _ast.identifier().text(); }
	};
}

#endif
