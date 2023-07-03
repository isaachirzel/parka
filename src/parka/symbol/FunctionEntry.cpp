#include "parka/symbol/FunctionEntry.hpp"
#include "parka/validator/Validator.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	ir::FunctionIr *FunctionEntry::resolve()
	{
		// TODO: Mutex
		_ir = validator::validateFunction(_ast, _symbolTable);
		_isValidated = true;

		return _ir;
	}
}
