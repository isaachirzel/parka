#include "parka/validation/GlobalContext.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ir/BoolPrimitiveIr.hpp"
#include "parka/ir/CharPrimitiveIr.hpp"
#include "parka/ir/I32PrimitiveIr.hpp"
#include "parka/ir/StringPrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/validation/FunctionEntry.hpp"
#include <stdexcept>

namespace parka::validation
{
	GlobalContext::GlobalContext(const ast::PackageAst& globalPackage):
		Context(ContextType::Global),
		_scope(""),
		_symbols(0),
		_functions(1'000'000),
		_intrinsics(1'000)
	{
		// addIntrinsic(ir::VoidPrimitiveIr::voidPrimitive);
		// addIntrinsic(ir::IntegerPrimitiveIr::u8Primitive);
		// addIntrinsic(ir::IntegerPrimitiveIr::u16Primitive);
		// addIntrinsic(ir::IntegerPrimitiveIr::u32Primitive);
		// addIntrinsic(ir::IntegerPrimitiveIr::u64Primitive);
		// addIntrinsic(ir::IntegerPrimitiveIr::i8Primitive);
		// addIntrinsic(ir::IntegerPrimitiveIr::i16Primitive);
		addIntrinsic(ir::I32PrimitiveIr::instance);
		// addIntrinsic(ir::IntegerPrimitiveIr::i64Primitive);
		// addIntrinsic(ir::FloatPrimitiveIr::f32Primitive);
		// addIntrinsic(ir::FloatPrimitiveIr::f64Primitive);
		addIntrinsic(ir::CharPrimitiveIr::instance);
		addIntrinsic(ir::BoolPrimitiveIr::instance);
		addIntrinsic(ir::StringPrimitiveIr::instance);

		for (auto& mod : globalPackage.modules())
		{
			for (auto *function : mod.functions())
			{
				declare(*function);
			}
		}
	}

	void GlobalContext::addIntrinsic(ir::EntityIr& intrinsic)
	{
		auto& entry = _intrinsics.push(IntrinsicEntry(intrinsic));
		
		_symbols.insert(intrinsic.symbol(), &entry);
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

	ir::EntityIr* GlobalContext::resolveSymbol(const ast::QualifiedIdentifierAst& identifier)
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
}
