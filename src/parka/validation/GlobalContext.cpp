#include "parka/validation/GlobalContext.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/validation/AssignmentOperatorKey.hpp"
#include "parka/validation/BinaryOperatorKey.hpp"
#include "parka/validation/FunctionEntry.hpp"
#include "parka/validation/IntrinsicFunction.hpp"
#include <stdexcept>

namespace parka::validation
{
	GlobalContext::GlobalContext(const ast::PackageAst& globalPackage):
		Context(ContextType::Global),
		_scope(""),
		_symbols(0),
		_binaryOperators(ir::BinaryOperatorIr::getIntrinsicBinaryOperators()),
		_conversions(ir::ConversionIr::getIntrinsicConversions()),
		_assignmentOperators(ir::AssignmentOperatorIr::getIntrinsicAssignmentOperators()),
		_functions(),
		_intrinsicFunctions()
	{
		addIntrinsicFunctions(_intrinsicFunctions, _symbols);

		for (usize i = 0; i < ir::PrimitiveIr::entryCount; ++i)
		{
			auto* primitive = ir::PrimitiveIr::entries[i];

			_symbols.insert(primitive->name(), primitive);
		}

		for (auto& mod : globalPackage.modules())
		{
			for (auto *function : mod.functions())
			{
				declare(*function);
			}
		}
	}

	FunctionEntry& GlobalContext::addFunction(FunctionEntry&& entry)
	{
		return _functions.push(std::move(entry));
	}

	FunctionEntry& GlobalContext::declare(const ast::FunctionAst& ast)
	{
		auto& entry = addFunction(FunctionEntry(ast, *this));
		const auto& key = ast.prototype().identifier().text();
		auto insertion = _symbols.insert(key, &entry);

		if (!insertion)
		{
			auto* previous = *insertion;

			log::error(ast.prototype().identifier(), "A $ with the name `$` has already been declared in global scope.", previous->resolvableType, previous->name());
		}

		return entry;
	}

	VariableEntry& GlobalContext::declare(const ast::VariableAst&)
	{
		throw std::invalid_argument("Variables cannot be declared in a GlobalContext.");
	}

	ParameterEntry& GlobalContext::declare(const ast::ParameterAst&)
	{
		throw std::invalid_argument("Parameters cannot be declared in a GlobalContext.");
	}

	Resolvable* GlobalContext::findSymbol(const ast::IdentifierAst& identifier)
	{
		auto& text = identifier.text();
		auto** result = _symbols.find(text);

		if (result)
			return *result;

		return {};
	}

	ir::LValueIr* GlobalContext::resolveSymbol(const ast::QualifiedIdentifierAst& identifier)
	{
		auto* entry = findSymbol(identifier[0]);

		if (!entry)
			return {};

		for (usize i = 1; i < identifier.length(); ++i)
		{
			if (!entry)
				return {};

			auto& part = identifier[i];
			auto* table = entry->context();

			if (!table)
			{
				log::error(identifier.snippet(),"No definition for `$` couble be found in package `$`.", part, entry->name());
				return {};
			}

			entry = table->findSymbol(part);
		}

		if (entry)
			return entry->resolve();
		
		return {};
	}

	ir::BinaryOperatorIr* GlobalContext::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right)
	{
		auto key = BinaryOperatorKey(left, right, binaryExpressionType);

		auto* op = _binaryOperators.find(key);

		if (!op)
			return {};

		return *op;
	}

	ir::AssignmentOperatorIr* GlobalContext::resolveAssignmentOperator(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType)
	{
		auto key = AssignmentOperatorKey(left, right, assignmentType);
		auto* op = _assignmentOperators.find(key);

		if (!op)
			return {};

		return *op;
	}

	Result<ir::ConversionIr*> GlobalContext::resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from)
	{
		if (from == to)
			return nullptr;

		auto key = ConversionKey(to, from);

		auto** conversion = _conversions.find(key);

		if (!conversion)
			return {};

		return *conversion;
	}
}
