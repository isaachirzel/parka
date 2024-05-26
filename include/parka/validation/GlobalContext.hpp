#ifndef PARKA_VALIDATION_GLOBAL_CONTEXT_HPP
#define PARKA_VALIDATION_GLOBAL_CONTEXT_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/PackageAst.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/validation/AssignmentOperatorKey.hpp"
#include "parka/validation/BinaryOperatorKey.hpp"
#include "parka/validation/ConversionKey.hpp"
#include "parka/validation/Context.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/FlatMap.hpp"
#include "parka/validation/IntrinsicFunctionEntry.hpp"

namespace parka::validation
{
	class GlobalContext: public Context
	{
		String _scope;
		FlatMap<String, Resolvable*> _symbols;
		FlatMap<BinaryOperatorKey, ir::BinaryOperatorIr*> _binaryOperators;
		FlatMap<ConversionKey, ir::ConversionIr*> _conversions;
		FlatMap<AssignmentOperatorKey, ir::AssignmentOperatorIr*> _assignmentOperators;
		Array<FunctionEntry> _functions;
		Array<IntrinsicFunctionEntry> _intrinsicFunctions;

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
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		ir::AssignmentOperatorIr* resolveAssignmentOperator(const ir::TypeIr& to, const ir::TypeIr& from, AssignmentType assignmentType);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from);
		const String& scope() const { return _scope; }
		Context* parent() { return nullptr; }
		GlobalContext& globalContext() { return *this; }

		auto& functions() { return _functions; }
	};
}

#endif
