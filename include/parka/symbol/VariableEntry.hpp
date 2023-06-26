#ifndef PARKA_SYMBOL_VARIABLE_ENTRY_HPP
#define PARKA_SYMBOL_VARIABLE_ENTRY_HPP

#include "parka/ast/Variable.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class VariableEntry: public Resolvable
	{
		const ast::VariableAst& _ast;
		// const ir::VariableIr *_ir;

	public:

		VariableEntry(const ast::VariableAst& ast, SymbolTable&):
		Resolvable(ResolvableType::Variable),
		_ast(ast)
		{}
		VariableEntry(VariableEntry&&) = default;
		VariableEntry(const VariableEntry&) = delete;

		const ir::VariableIr *resolve();

		const auto& ast() const { return _ast; }
		const String& name() const { return _ast.name(); }
	};
}

#endif
