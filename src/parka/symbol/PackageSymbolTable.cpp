#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/IntrinsicConversionIr.hpp"
#include "parka/ir/IntrinsicBinaryOperatorIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	PackageSymbolTable::PackageSymbolTable(const ast::PackageAst& ast, PackageSymbolTable* parent):
		SymbolTable(SymbolTableType::Package),
		_scope(parent != nullptr ? parent->createSymbol(ast.name()) : ast.name()),
		_symbols(),
		_operators(),
		_conversions(),
		_functions(),
		_parent(parent)
	{
		// TODO: Actual error checking
		const auto isGlobalPackage = _parent == nullptr;

		if (isGlobalPackage)
		{
			for (usize i = 0; i < ir::Primitive::entryCount; ++i)
			{
				auto* primitive = ir::Primitive::entries[i];

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
		}

		for (auto& mod : ast.modules())
		{
			// for (auto *strct : mod.structs())
			// 	strct->declareSelf(*this);

			for (auto *function : mod.functions())
			{
				auto& resolvable = _functions.push(FunctionEntry(*function, *this));
				const auto& key = function->prototype().identifier().text();

				_symbols.insert(key, &resolvable);
			}
		}

		// TODO: Add other packages
		// for (auto *package : _packages)
		// 	package->declareSelf(this);
	}

	Resolvable* PackageSymbolTable::findInitialSymbol(const ast::Identifier& identifier)
	{
		const auto& name = identifier.text();
		auto *package = this;

		do
		{
			auto *entry = package->findSymbol(identifier);

			if (entry != nullptr)
				return entry;

			if (entry->name() == name)
				return entry;

			package = package->_parent;
		}
		while (package != nullptr);

		return nullptr;
	}

	Resolvable* PackageSymbolTable::findAbsoluteSymbol(const ast::Identifier& identifier)
	{
		auto *package = this;
		auto *parent = _parent;
		
		while (parent != nullptr)
		{
			package = parent;
			parent = package->_parent;
		}

		auto *entry = package->findSymbol(identifier);

		return entry;
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
		// TODO: Optimize absolute package
		const auto& first = qualifiedIdentifier[0];
		auto *entry = qualifiedIdentifier.isAbsolute()
			? findInitialSymbol(first)
			: findAbsoluteSymbol(first);

		for (usize i = 1; i < qualifiedIdentifier.length(); ++i)
		{
			if (entry == nullptr)
				break;

			const auto& identifier = qualifiedIdentifier[i];
			auto *table = dynamic_cast<SymbolTable*>(entry);

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

	Result<ir::ConversionIr*> PackageSymbolTable::resolveConversion(const ir::Type& to, const ir::Type& from)
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

	std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& symbolTable)
	{
		auto indent = Indent(out);

		out << indent;

		if (symbolTable._parent == nullptr)
		{
			out << "global\n";
		}
		else
		{
			out << "package\n";
		}

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
