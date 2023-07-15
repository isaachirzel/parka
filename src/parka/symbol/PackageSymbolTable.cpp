#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ir/Package.hpp"
#include "parka/ir/Primitive.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"

namespace parka
{
	PackageSymbolTable::PackageSymbolTable(const ast::PackageAst& ast, PackageSymbolTable *parent):
	SymbolTable(SymbolTableType::Package),
	_scope(parent != nullptr ? parent->createSymbol(ast.name()) : ast.name()),
	_symbols(),
	_functions(),
	_parent(parent)
	{
		// TODO: Actual error checking
		const auto isGlobalPackage = _parent == nullptr;

		if (isGlobalPackage)
		{
			for (usize i = 0; i < ir::Primitive::entryCount; ++i)
			{
				auto& primitive = ir::Primitive::entries[i];

				_symbols.insert(primitive.name(), &primitive);
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

		// for (auto *package : _packages)
		// 	package->declareSelf(this);
	}

	Resolvable *PackageSymbolTable::findInitial(const ast::Identifier& identifier)
	{
		const auto& name = identifier.text();
		auto *package = this;

		do
		{
			auto *entry = package->find(identifier);

			if (entry != nullptr)
				return entry;

			if (entry->name() == name)
				return entry;

			package = package->_parent;
		}
		while (package != nullptr);

		return nullptr;
	}

	Resolvable *PackageSymbolTable::findAbsolute(const ast::Identifier& identifier)
	{
		auto *package = this;
		auto *parent = _parent;
		
		while (parent != nullptr)
		{
			package = parent;
			parent = package->_parent;
		}

		auto *entry = package->find(identifier);

		return entry;
	}

	Resolvable *PackageSymbolTable::find(const ast::Identifier& identifier)
	{
		auto result = _symbols.find(identifier.text());

		if (result != nullptr)
			return *result;

		return nullptr;
	}

	Resolution *PackageSymbolTable::resolve(const ast::QualifiedIdentifier& qualifiedIdentifier)
	{
		// TODO: Optimize absolute package
		const auto& first = qualifiedIdentifier[0];
		auto *entry = qualifiedIdentifier.isAbsolute()
			? findInitial(first)
			: findAbsolute(first);

		for (usize i = 1; i < qualifiedIdentifier.length(); ++i)
		{
			if (entry == nullptr)
				break;

			const auto& identifier = qualifiedIdentifier[i];
			auto *table = dynamic_cast<SymbolTable*>(entry);

			if (table == nullptr)
			{
				log::error("Unable to resolve $ in $ $.", identifier, entry->resolvableType, entry->name());
				return nullptr;
			}

			entry = table->find(identifier);
		}

		if (entry != nullptr)
			return entry->resolve();
			// return entry->context();

		// TODO: Use index to shorten the symbol so it is more specific what could not be found
		log::error("Unable to find $ in this scope.", qualifiedIdentifier);

		return nullptr;
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
