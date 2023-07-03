#ifndef PARKA_SYMBOL_PARAMETER_ENTRY_HPP
#define PARKA_SYMBOL_PARAMETER_ENTRY_HPP

#include "parka/ast/Parameter.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	class ParameterEntry: public Resolvable
	{
		const ast::ParameterAst& _ast;
		ir::ParameterIr *_ir;

	public:

		ParameterEntry(const ast::ParameterAst& ast, ir::ParameterIr *ir):
		Resolvable(ResolvableType::Parameter),
		_ast(ast),
		_ir(ir)
		{}
		ParameterEntry(ParameterEntry&&) = default;
		ParameterEntry(const ParameterEntry&) = delete;

		ir::ParameterIr *resolve();

		const auto& ast() const { return _ast; }
		const auto *ir() const { return _ir; }
		const String& name() const { return _ast.identifier().text(); }
		const ast::Identifier& identifier() const { return _ast.identifier(); }
	};
}

#endif
