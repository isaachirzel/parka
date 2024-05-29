#include "parka/validation/FunctionEntry.hpp"
#include "parka/validation/Validator.hpp"

namespace parka::validation
{
	FunctionEntry::FunctionEntry(const ast::FunctionAst& ast, Context& context):
		ContextEntry(ResolvableType::Function),
		_ast(ast),
		_symbolTable(context),
		_ir(nullptr),
		_isValidated(false)
	{}

	ir::FunctionIr *FunctionEntry::resolve()
	{
		if (_isValidated)
			return _ir;

		// TODO: Mutex
		_ir = validation::validateFunction(_ast, _symbolTable);
		_isValidated = true;

		return _ir;
	}
}
