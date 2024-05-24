#include "parka/symbol/FunctionEntry.hpp"
#include "parka/validation/Validator.hpp"

namespace parka
{
	FunctionEntry::FunctionEntry(const ast::FunctionAst& ast, SymbolTable& symbolTable):
		Resolvable(ResolvableType::Function),
		_ast(ast),
		_symbolTable(symbolTable),
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
