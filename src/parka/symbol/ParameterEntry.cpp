#include "parka/symbol/ParameterEntry.hpp"

namespace parka
{
	ParameterEntry::ParameterEntry(const ast::ParameterAst& ast, ir::ParameterIr *ir):
		Resolvable(ResolvableType::Parameter),
		_ast(ast),
		_ir(ir)
	{}

	ir::ParameterIr* ParameterEntry::resolve()
	{
		return _ir;
	}
}
