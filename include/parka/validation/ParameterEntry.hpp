#ifndef PARKA_VALIDATION_PARAMETER_ENTRY_HPP
#define PARKA_VALIDATION_PARAMETER_ENTRY_HPP

#include "parka/ast/ParameterAst.hpp"
#include "parka/validation/Resolvable.hpp"

namespace parka::validation
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

		Context* context() { return nullptr; }
		const auto& ast() const { return _ast; }
		const String& name() const { return _ast.identifier().text(); }
		const ast::IdentifierAst& identifier() const { return _ast.identifier(); }
	};
}

#endif
