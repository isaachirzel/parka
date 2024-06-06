#ifndef PARKA_VALIDATION_FUNCTION_ENTRY_HPP
#define PARKA_VALIDATION_FUNCTION_ENTRY_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/validation/FunctionContext.hpp"
#include "parka/validation/ContextEntry.hpp"
#include "parka/validation/Context.hpp"

namespace parka::validation
{
	class FunctionEntry: public ContextEntry
	{
		const ast::FunctionAst& _ast;
		FunctionContext _context;
		ir::FunctionIr *_ir;
		bool _isValidated;

	public:

		FunctionEntry(const ast::FunctionAst& ast, Context& context);
		FunctionEntry(FunctionEntry&&) = default;
		FunctionEntry(const FunctionEntry&) = delete;

		ir::FunctionIr* resolve();
		FunctionContext* context() { return &_context; }

		const auto& ast() const { return _ast; }
		const ast::IdentifierAst& identifier() const { return _ast.prototype().identifier(); }
		const String& name() const { return _ast.prototype().identifier().text(); }
	};
}

#endif
