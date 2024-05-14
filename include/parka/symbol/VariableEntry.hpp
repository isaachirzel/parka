#ifndef PARKA_SYMBOL_VARIABLE_ENTRY_HPP
#define PARKA_SYMBOL_VARIABLE_ENTRY_HPP

#include "parka/ast/VariableAst.hpp"
#include "parka/ir/VariableIr.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class VariableEntry: public Resolvable
	{
		const ast::VariableAst& _ast;
		ir::VariableIr *_ir;

	public:

		VariableEntry(const ast::VariableAst& ast, ir::VariableIr *ir):
		Resolvable(ResolvableType::Variable),
		_ast(ast),
		_ir(ir)
		{}
		VariableEntry(VariableEntry&&) = default;
		VariableEntry(const VariableEntry&) = delete;

		ir::VariableIr *resolve() { return _ir; }

		const auto& ast() const { return _ast; }
		const auto *ir() const { return _ir; }
		const ast::Identifier& identifier() const { return _ast.identifier(); }
		const String& name() const { return _ast.identifier().text(); }
	};
}

#endif
