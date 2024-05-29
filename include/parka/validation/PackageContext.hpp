#ifndef PARKA_VALIDATION_PACKAGE_CONTEXT_HPP
#define PARKA_VALIDATION_PACKAGE_CONTEXT_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/validation/GlobalContext.hpp"
#include "parka/validation/Resolvable.hpp"
#include "parka/validation/Context.hpp"

namespace parka::validation
{
	class PackageContext: public Context
	{
		String _scope;
		FlatMap<String, Resolvable*> _symbols;
		GlobalContext& _global;
		Context& _parent;

	public:

		PackageContext(const ast::PackageAst& ast, Context& parent);
		PackageContext(PackageContext&&) = default;
		PackageContext(const PackageContext&) = delete;

		FunctionEntry& declare(const ast::FunctionAst& ast);
		VariableEntry& declare(const ast::VariableAst& ast);
		ParameterEntry& declare(const ast::ParameterAst& ast);
		Resolvable* findSymbol(const ast::IdentifierAst& identifier);
		Resolvable* findInitialSymbol(const ast::IdentifierAst& identifier);
		ir::EntityIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);

		const String& scope() const { return _scope; }
		Context* parent() { return &_parent; }
		GlobalContext& globalContext() { return _global; }
	};
}

#endif
