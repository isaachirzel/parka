#include "parka/validation/GlobalContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/validation/FunctionContext.hpp"
#include "parka/validation/FunctionEntry.hpp"
#include "parka/validation/I32TypeContext.hpp"
#include "parka/log/Log.hpp"
#include "parka/validation/IntegerTypeContext.hpp"

namespace parka::validation
{
	GlobalContext::GlobalContext(const ast::PackageAst& globalPackage):
		Context(ContextType::Global),
		_scope(""),
		_symbols(0),
		_functions(1'000'000),
		_intrinsics(1'000)
	{
		_types.insert(&ir::PrimitiveIr::integerPrimitive, &IntegerTypeContext::instance);

		addPrimitive(ir::PrimitiveIr::u8Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::u16Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::u32Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::u64Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::i8Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::i16Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::i32Primitive, &I32TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::i64Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::f32Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::f64Primitive, nullptr);
		addPrimitive(ir::PrimitiveIr::charPrimitive, nullptr);
		addPrimitive(ir::PrimitiveIr::boolPrimitive, nullptr);
		addPrimitive(ir::PrimitiveIr::stringPrimitive, nullptr);

		for (auto& mod : globalPackage.modules())
		{
			for (auto *function : mod.functions())
			{
				declare(*function);
			}
		}
	}

	void GlobalContext::addPrimitive(ir::PrimitiveIr& primitive, TypeContext* typeContext)
	{
		addIntrinsic(primitive);
		
		if (typeContext)
			_types.insert(&primitive, typeContext);
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
		auto functionContext = FunctionContext(*this);
		auto& entry = addFunction(FunctionEntry(ast, *this));
		const auto& key = ast.prototype().identifier().text();
		auto insertion = _symbols.insert(key, &entry);

		if (!insertion)
		{
			auto& previous = **insertion;

			log::error(ast.prototype().identifier(), "A $ with the name `$` has already been declared in global scope.", previous.entityType, previous.name());
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
		auto* iter = _types.find(&type);

		if (!iter)
			log::fatal("Unable to get context for type `$`.", type);

		return **iter;
	}
}