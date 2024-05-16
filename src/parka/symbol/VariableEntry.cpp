#include "parka/symbol/VariableEntry.hpp"

namespace parka
{
	VariableEntry::VariableEntry(const ast::VariableAst& ast, ir::VariableIr *ir):
		Resolvable(ResolvableType::Variable),
		_ast(ast),
		_ir(ir)
	{}

	ir::VariableIr *VariableEntry::resolve()
	{
		return _ir;
	}
}
