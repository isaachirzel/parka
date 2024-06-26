#include "parka/validation/ParameterEntry.hpp"

namespace parka::validation
{
	ParameterEntry::ParameterEntry(const ast::ParameterAst& ast, ir::ParameterIr *ir):
		ContextEntry(EntityType::Parameter),
		_ast(ast),
		_ir(ir)
	{}

	ir::ParameterIr* ParameterEntry::resolve()
	{
		return _ir;
	}
}
