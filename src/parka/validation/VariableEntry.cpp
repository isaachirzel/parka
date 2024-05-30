#include "parka/validation/VariableEntry.hpp"

namespace parka::validation
{
	VariableEntry::VariableEntry(const ast::VariableAst& ast, ir::VariableIr *ir):
		ContextEntry(EntityType::Variable),
		_ast(ast),
		_ir(ir)
	{}

	ir::VariableIr *VariableEntry::resolve()
	{
		return _ir;
	}
}
