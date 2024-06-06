#include "parka/validation/FunctionEntry.hpp"
#include "parka/validation/Validator.hpp"

namespace parka::validation
{
	FunctionEntry::FunctionEntry(const ast::FunctionAst& ast, Context& context):
		ContextEntry(EntityType::Function),
		_ast(ast),
		_context(context),
		_ir(nullptr),
		_isValidated(false)
	{}

	ir::FunctionIr* FunctionEntry::resolve()
	{
		if (!_isValidated)
		{
			_ir = validateFunction(_ast, _context);
			_isValidated = true;
		}

		return _ir;
	}
}
