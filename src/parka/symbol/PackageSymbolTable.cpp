#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/FunctionEntry.hpp"
#include <stdexcept>

namespace parka
{
	PackageSymbolTable::PackageSymbolTable(const ast::PackageAst& ast, SymbolTable& parent):
		SymbolTable(SymbolTableType::Package),
		_scope(parent.createSymbol(ast.name())),
		_symbols(),
		_global(parent.globalSymbolTable()),
		_parent(parent)
	{
		log::notImplemented(here());
	}

	FunctionEntry& PackageSymbolTable::declare(const ast::FunctionAst& ast)
	{
		auto& entry = _global.addFunction(FunctionEntry(ast, *this));
		const auto& key = ast.prototype().identifier().text();
		auto insertion = _symbols.insert(key, &entry);

		if (!insertion)
		{
			auto* previous = *insertion;

			log::error(ast.prototype().identifier(), "A $ with the name `$` has already been declared in the package $.", previous->resolvableType, previous->name(), _scope);
		}

		return entry;
	}

	VariableEntry& PackageSymbolTable::declare(const ast::VariableAst&)
	{
		throw std::invalid_argument("Variables cannot be declared in a PackageSymbolTable.");
	}

	ParameterEntry& PackageSymbolTable::declare(const ast::ParameterAst&)
	{
		throw std::invalid_argument("Parameters cannot be declared in a PackageSymbolTable.");

	}

	Resolvable* PackageSymbolTable::findInitialSymbol(const ast::IdentifierAst& identifier)
	{
		const auto& name = identifier.text();
		auto *package = (SymbolTable*)this;

		do
		{
			auto *entry = package->findSymbol(identifier);

			if (entry != nullptr)
				return entry;

			if (entry->name() == name)
				return entry;

			package = package->parent();
		}
		while (package != nullptr);

		return nullptr;
	}

	Resolvable* PackageSymbolTable::findSymbol(const ast::IdentifierAst& identifier)
	{
		auto result = _symbols.find(identifier.text());

		if (result != nullptr)
			return *result;

		return nullptr;
	}

	ir::LValueIr* PackageSymbolTable::resolveSymbol(const ast::QualifiedIdentifier& qualifiedIdentifier)
	{
		if (qualifiedIdentifier.isAbsolute())
			return _global.resolveSymbol(qualifiedIdentifier);

		const auto& first = qualifiedIdentifier[0];
		auto *entry = findInitialSymbol(first);

		for (usize i = 1; i < qualifiedIdentifier.length(); ++i)
		{
			if (entry == nullptr)
				break;

			// TODO: Figure out how to not use dynamic cast in this

			const auto& identifier = qualifiedIdentifier[i];
			auto *table = entry->symbolTable();

			if (table == nullptr)
			{
				log::error("Unable to resolve `$` in package `$`.", identifier, entry->name());
				return nullptr;
			}

			entry = table->findSymbol(identifier);
		}

		if (entry != nullptr)
			return entry->resolve();

		return nullptr;
	}

	ir::BinaryOperatorIr* PackageSymbolTable::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right)
	{
		return _global.resolveBinaryOperator(binaryExpressionType, left, right);
	}

	Result<ir::ConversionIr*> PackageSymbolTable::resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from)
	{
		return _global.resolveConversion(to, from);
	}
}
