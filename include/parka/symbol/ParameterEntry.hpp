#ifndef PARKA_SYMBOL_PARAMETER_ENTRY_HPP
#define PARKA_SYMBOL_PARAMETER_ENTRY_HPP

#include "parka/ast/Parameter.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class ParameterEntry: public Resolvable
	{
		const ast::ParameterAst& _ast;
		// const ir::VariableIr& _ir;

	public:

		ParameterEntry(const ast::ParameterAst& ast, SymbolTable&):
		Resolvable(ResolvableType::Parameter),
		_ast(ast)
		// _ir(validator::validate(ast, symbolTable)),
		{}
		ParameterEntry(ParameterEntry&&) = default;
		ParameterEntry(const ParameterEntry&) = delete;

		const auto& ast() const { return _ast; }
		const String& name() const { return _ast.name(); }
	};
}

#endif
