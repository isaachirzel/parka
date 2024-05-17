#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	PackageSymbolTable::PackageSymbolTable(const ast::PackageAst& ast, SymbolTable& parent):
		SymbolTable(SymbolTableType::Package),
		_scope(parent.createSymbol(ast.name())),
		_symbols(),
		_global(parent.global()),
		_parent(parent)
	{
		log::notImplemented(here());
		// TODO: Actual error checking
		// for (auto& mod : ast.modules())
		// {
		// 	for (auto *function : mod.functions())
		// 	{
		// 		_global.declare(*function);
		// 	}
		// }

		// TODO: Add other packages
		// for (auto *package : _packages)
		// 	package->declareSelf(this);
	}

	Resolvable* PackageSymbolTable::findInitialSymbol(const ast::Identifier& identifier)
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

	Resolvable* PackageSymbolTable::findSymbol(const ast::Identifier& identifier)
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

	ir::BinaryOperatorIr* PackageSymbolTable::resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::Type& left, const ir::Type& right)
	{
		return _global.resolveBinaryOperator(binaryExpressionType, left, right);
	}

	Result<ir::ConversionIr*> PackageSymbolTable::resolveConversion(const ir::Type& to, const ir::Type& from)
	{
		return _global.resolveConversion(to, from);
	}

	std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& symbolTable)
	{
		auto indent = Indent(out);

		out << indent << "package\n";
		out << indent << "{\n";

		{
			auto subindent = Indent(out);

			out << subindent << "symbols\n";
			out << subindent << "{\n";

			{
				auto subsubindent = Indent(out);

				for (const auto& entry : symbolTable._symbols)
				{
					out << subsubindent << *entry.value() << '\n';
				}

			}

			out << subindent << "}\n\n";
		}

		// for (const auto& mod : symbolTable.modules())
		// {
		// 	out << mod << '\n';
		// }

		// for (const auto *package : symbolTable._packages)
		// {
		// 	out << *package << '\n';
		// }

		out << indent << "}";

		return out;
	}
}
