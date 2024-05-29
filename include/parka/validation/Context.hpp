#ifndef PARKA_VALIDATION_CONTEXT_HPP
#define PARKA_VALIDATION_CONTEXT_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/enum/ContextType.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ir/EntityIr.hpp"

namespace parka::validation
{
	class GlobalContext;
	struct Resolvable;
	class FunctionEntry;
	class VariableEntry;
	class ParameterEntry;

	struct Context
	{
		const ContextType symbolTableType;

		Context(ContextType symbolTableType):
			symbolTableType(symbolTableType)
		{}
		virtual ~Context() {}

		virtual FunctionEntry& declare (const ast::FunctionAst& ast) = 0;
		virtual VariableEntry& declare (const ast::VariableAst& ast) = 0;
		virtual ParameterEntry& declare (const ast::ParameterAst& ast) = 0;
		virtual Resolvable* findSymbol(const ast::IdentifierAst& identifier) = 0;
		virtual ir::EntityIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier) = 0;
		virtual const String& scope() const = 0;
		virtual Context* parent() = 0;
		virtual GlobalContext& globalContext() = 0;

		String createSymbol(const String& name) const
		{
			const auto& scope = this->scope();

			if (scope.empty())
				return name;

			auto length = scope.length() + 2 + name.length();
			auto symbol = String();

			symbol.reserve(length);
			symbol += scope;
			symbol += "::";
			symbol += name;

			return symbol;
		}
	};
}

#endif
