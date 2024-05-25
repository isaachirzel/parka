#ifndef PARKA_VALIDATION_PACKAGE_CONTEXT_HPP
#define PARKA_VALIDATION_PACKAGE_CONTEXT_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
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
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		ir::AssignmentOperatorIr* resolveAssignmentOperator(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& from, const ir::TypeIr& to);

		const String& scope() const { return _scope; }
		Context* parent() { return &_parent; }
		GlobalContext& globalContext() { return _global; }
	};
}

#endif
