#include "parka/validation/GlobalContext.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/validation/BoolTypeContext.hpp"
#include "parka/validation/CharTypeContext.hpp"
#include "parka/validation/F32TypeContext.hpp"
#include "parka/validation/F64TypeContext.hpp"
#include "parka/validation/FloatTypeContext.hpp"
#include "parka/validation/FunctionContext.hpp"
#include "parka/validation/FunctionEntry.hpp"
#include "parka/validation/I16TypeContext.hpp"
#include "parka/validation/I32TypeContext.hpp"
#include "parka/log/Log.hpp"
#include "parka/validation/I64TypeContext.hpp"
#include "parka/validation/I8TypeContext.hpp"
#include "parka/validation/IntegerTypeContext.hpp"
#include "parka/validation/U16TypeContext.hpp"
#include "parka/validation/U32TypeContext.hpp"
#include "parka/validation/U64TypeContext.hpp"
#include "parka/validation/U8TypeContext.hpp"

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
		_types.insert(&ir::PrimitiveIr::floatPrimitive, &FloatTypeContext::instance);

		addPrimitive(ir::PrimitiveIr::u8Primitive, &U8TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::u16Primitive, &U16TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::u32Primitive, &U32TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::u64Primitive, &U64TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::i8Primitive, &I8TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::i16Primitive, &I16TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::i32Primitive, &I32TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::i64Primitive, &I64TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::f32Primitive, &F32TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::f64Primitive, &F64TypeContext::instance);
		addPrimitive(ir::PrimitiveIr::charPrimitive, &CharTypeContext::instance);
		addPrimitive(ir::PrimitiveIr::boolPrimitive, &BoolTypeContext::instance);
		// addPrimitive(ir::PrimitiveIr::stringPrimitive, &StringTypeContext::instance); 

		addIntrinsic(ir::FunctionIr::printlnFunction);
		addIntrinsic(ir::FunctionIr::printIntFunction);

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

			log::shadowedGlobalEntityError(ast.prototype().identifier(), previous.name(), previous.entityType);
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
				log::undefinedPackageEntityError(identifier.snippet(), part.text(), entry->name());
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

		assert(iter != nullptr);

		return **iter;
	}
}
