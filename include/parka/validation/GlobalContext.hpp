#ifndef PARKA_VALIDATION_GLOBAL_CONTEXT_HPP
#define PARKA_VALIDATION_GLOBAL_CONTEXT_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/PackageAst.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/validation/Context.hpp"
#include "parka/util/BigArray.hpp"
#include "parka/util/FlatMap.hpp"
#include "parka/validation/IntrinsicEntry.hpp"

namespace parka::validation
{
	class GlobalContext: public Context
	{
		String _scope;
		FlatMap<String, Resolvable*> _symbols;
		BigArray<FunctionEntry> _functions;
		BigArray<IntrinsicEntry> _intrinsics;

	private:

		void addIntrinsic(ir::LValueIr& intrinsic);

	public:

		GlobalContext(const ast::PackageAst& globalPackage);
		GlobalContext(GlobalContext&&) = default;
		GlobalContext(const GlobalContext&) = delete;

		FunctionEntry& addFunction(FunctionEntry&& entry);

		FunctionEntry& declare(const ast::FunctionAst& ast);
		VariableEntry& declare(const ast::VariableAst& ast);
		ParameterEntry& declare(const ast::ParameterAst& ast);
		Resolvable* findSymbol(const ast::IdentifierAst& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);
		const String& scope() const { return _scope; }
		Context* parent() { return nullptr; }
		GlobalContext& globalContext() { return *this; }

		auto& functions() { return _functions; }
	};
}

#endif
