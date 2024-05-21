#ifndef PARKA_SYMBOL_PARAMETER_ENTRY_HPP
#define PARKA_SYMBOL_PARAMETER_ENTRY_HPP

#include "parka/ast/ParameterAst.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class ParameterEntry: public Resolvable
	{
		const ast::ParameterAst& _ast;
		ir::ParameterIr *_ir;

	public:

		ParameterEntry(const ast::ParameterAst& ast, ir::ParameterIr *ir);
		ParameterEntry(ParameterEntry&&) = default;
		ParameterEntry(const ParameterEntry&) = delete;

		ir::ParameterIr *resolve();

		SymbolTable* symbolTable() { return nullptr; }
		const auto& ast() const { return _ast; }
		const String& name() const { return _ast.identifier().text(); }
		const ast::IdentifierAst& identifier() const { return _ast.identifier(); }
	};
}

#endif
