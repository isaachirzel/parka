#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ir/IntrinsicBinaryOperatorIr.hpp"
#include "parka/ir/IntrinsicConversionIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	GlobalSymbolTable::GlobalSymbolTable(const ast::PackageAst& globalPackage):
		SymbolTable(SymbolTableType::Global),
		_scope(""),
		_symbols(),
		_operators(),
		_conversions(),
		_functions()
	{
		for (usize i = 0; i < ir::PrimitiveIr::entryCount; ++i)
		{
			auto* primitive = ir::PrimitiveIr::entries[i];

			_symbols.insert(primitive->name(), primitive);
		}

		for (usize i = 0; i < ir::IntrinsicBinaryOperatorIr::entryCount; ++i)
		{
			auto& op = ir::IntrinsicBinaryOperatorIr::entries[i];

			_operators.push(&op);
		}

		for (usize i = 0; i < ir::IntrinsicConversionIr::entryCount; ++i)
		{
			auto& conv = ir::IntrinsicConversionIr::entries[i];

			_conversions.push(&conv);
		}

		for (auto& mod : globalPackage.modules())
		{
			for (auto *function : mod.functions())
			{
				declare(*function);
			}
		}
	}

	FunctionEntry& GlobalSymbolTable::addFunction(FunctionEntry&& entry)
	{
		return _functions.push(std::move(entry));
	}

	FunctionEntry* GlobalSymbolTable::declare(ast::FunctionAst& ast)
	{
		// TODO: Error checking
		auto& entry = addFunction(FunctionEntry(ast, *this));
		const auto& key = ast.prototype().identifier().text();
		auto* symbol = _symbols.insert(key, &entry);

		if (!symbol)
			return nullptr;

		return &entry;
	}

	Resolvable* GlobalSymbolTable::findSymbol(const ast::Identifier& identifier)
	{
		auto result = _symbols.find(identifier.text());

		if (result != nullptr)
			return *result;

		return nullptr;
	}

	ir::LValueIr* GlobalSymbolTable::resolveSymbol(const ast::QualifiedIdentifier& identifier)
	{
		auto* entry = findSymbol(identifier[0]);

		for (usize i = 1; i < identifier.length(); ++i)
		{
			if (entry == nullptr)
				break;

			// TODO: Figure out how to not use dynamic cast in this

			auto& part = identifier[i];
			auto* table = entry->symbolTable();

			if (table == nullptr)
			{
				log::error("Unable to resolve `$` in package `$`.", part, entry->name());
				return nullptr;
			}

			entry = table->findSymbol(part);
		}

		if (entry != nullptr)
			return entry->resolve();

		return nullptr;
	}

	ir::BinaryOperatorIr* GlobalSymbolTable::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right)
	{
		for (auto *op : _operators)
		{
			if (op->binaryExpressionType() != binaryExpressionType)
				continue;

			if (op->leftType() != left)
				continue;

			if (op->rightType() != right)
				continue;

			return op;
		}

		log::error("No operator `$ $ $` has been defined.", left, binaryExpressionType, right);

		return nullptr;
	}

	Result<ir::ConversionIr*> GlobalSymbolTable::resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from)
	{
		if (from == to)
			return nullptr;

		for (auto* conversion : _conversions)
		{
			if (conversion->to() == to && conversion->from() == from)
				return conversion;
		}

		return {};
	}

	const String& GlobalSymbolTable::scope() const
	{
		return _scope;
	}
}