#ifndef PARKA_VALIDATION_FUNCTION_CONTEXT_HPP
#define PARKA_VALIDATION_FUNCTION_CONTEXT_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/validation/LocalContext.hpp"
#include "parka/validation/ContextEntry.hpp"
#include "parka/validation/VariableEntry.hpp"
#include "parka/validation/ParameterEntry.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::validation
{
	struct ContextEntry;
	class GlobalContext;

	class FunctionContext: public LocalContext
	{
		GlobalContext& _global;
		Context& _parent;
		String _scope;
		FlatMap<String, ContextEntry*> _symbols;
		Array<VariableEntry> _variables;
		Array<ParameterEntry> _parameters;
		const ir::TypeIr* _returnType;
		bool _isExplicitReturnType;

	public:

		FunctionContext(Context &parent);
		FunctionContext(FunctionContext&&) = default;
		FunctionContext(const FunctionContext&) = delete;

		VariableEntry& addVariable(VariableEntry&& entry);
		ParameterEntry& addParameter(ParameterEntry&& entry);

		FunctionEntry& declare(const ast::FunctionAst& ast);
		VariableEntry& declare(const ast::VariableAst& ast);
		ParameterEntry& declare(const ast::ParameterAst& ast);
		ContextEntry* findSymbol(const ast::IdentifierAst& identifier);
		ir::EntityIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);
		
		void setReturnType(const ir::TypeIr& type) { _returnType = &type; }
		const ir::TypeIr& returnType() const { return *_returnType; }
		void setIsExplicitReturnType(bool value) { _isExplicitReturnType = value; }
		const auto& isExplicitReturnType() const { return _isExplicitReturnType; }
		const String& scope() const { return _scope; }
		Context* parent() { return &_parent; }
		GlobalContext& globalContext() { return _global; }
		FunctionContext& functionContext() { return *this; }
		bool isInLoop() const { return false; }
	};
}

#endif
