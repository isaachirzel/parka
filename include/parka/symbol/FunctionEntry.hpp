#ifndef PARKA_SYMBOL_FUNCTION_ENTRY_HPP
#define PARKA_SYMBOL_FUNCTION_ENTRY_HPP

#include "parka/ast/Function.hpp"
#include "parka/ir/Function.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class FunctionEntry: public Resolvable
	{
		const ast::FunctionAst& _ast;
		SymbolTable& _symbolTable;
		ir::FunctionIr *_ir;
		bool _isValidated;

	public:

		FunctionEntry(const ast::FunctionAst& ast, SymbolTable& symbolTable):
		Resolvable(ResolvableType::Function),
		_ast(ast),
		_symbolTable(symbolTable),
		_ir(nullptr),
		_isValidated(true)
		{}

		ir::FunctionIr *resolve();

		const auto& ast() const { return _ast; }
		const ast::Identifier& identifier() const { return _ast.prototype().identifier(); }
		const String& name() const { return _ast.prototype().identifier().text(); }
	};
}

#endif
