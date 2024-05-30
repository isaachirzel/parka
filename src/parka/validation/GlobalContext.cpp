#include "parka/validation/GlobalContext.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
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
		// addIntrinsic(ir::PrimitiveIr::voidPrimitive);
		// addIntrinsic(ir::PrimitiveIr::u8Primitive);
		// addIntrinsic(ir::PrimitiveIr::u16Primitive);
		// addIntrinsic(ir::PrimitiveIr::u32Primitive);
		// addIntrinsic(ir::PrimitiveIr::u64Primitive);
		// addIntrinsic(ir::PrimitiveIr::i8Primitive);
		// addIntrinsic(ir::PrimitiveIr::i16Primitive);
		addIntrinsic(ir::PrimitiveIr::i32Primitive);
		// addIntrinsic(ir::PrimitiveIr::i64Primitive);
		// addIntrinsic(ir::PrimitiveIr::f32Primitive);
		// addIntrinsic(ir::PrimitiveIr::f64Primitive);
		addIntrinsic(ir::PrimitiveIr::charPrimitive);
		addIntrinsic(ir::PrimitiveIr::boolPrimitive);
		addIntrinsic(ir::PrimitiveIr::stringPrimitive);

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

	ContextEntry* GlobalContext::findSymbol(const ast::IdentifierAst& identifier)
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

	TypeContext& GlobalContext::getTypeContext(const ir::TypeIr& type)
	{
		auto* context = _types.find(&type);

		if (!context)
		{
			auto ins = _types.insert(&type, TypeContext(*this));

			context = &*ins;
		}

		return *context;
	}
}
