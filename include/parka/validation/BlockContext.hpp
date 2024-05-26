#ifndef PARKA_VALIDATION_BLOCK_CONTEXT_HPP
#define PARKA_VALIDATION_BLOCK_CONTEXT_HPP

#include "parka/validation/FunctionContext.hpp"
#include "parka/validation/LocalContext.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::validation
{
	class BlockContext: public LocalContext
	{
		GlobalContext& _global;
		FunctionContext& _function;
		Context& _parent;
		String _scope;
		FlatMap<String, Resolvable*> _symbols;
		bool _isInLoop;

		BlockContext(FunctionContext& function, Context& parent);

	public:

		BlockContext(LocalContext& parent);
		BlockContext(BlockContext&&) = default;
		BlockContext(const BlockContext&) = delete;

		FunctionEntry& declare(const ast::FunctionAst& ast);
		VariableEntry& declare(const ast::VariableAst& ast);
		ParameterEntry& declare(const ast::ParameterAst& ast);
		Resolvable* findSymbol(const ast::IdentifierAst& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);
		const String& scope() const { return _scope; }
		Context* parent() { return &_parent; }
		const ir::TypeIr& returnType() const { return _function.returnType(); }
		void setInLoop() { _isInLoop = true; }
		bool isInLoop() const { return _isInLoop; }
		FunctionContext& functionContext() { return _function; }
		GlobalContext& globalContext() { return _global; }
	};
}

#endif
