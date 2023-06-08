#ifndef PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

// TODO: Move constructor

namespace parka
{
	class SymbolTableEntry;

	class PackageSymbolTable : public SymbolTable
	{
		const PackageSyntax& _syntax;
		Table<String, SymbolTableEntry> _symbols;
		const SymbolTable *_parent;

	private:
		
		bool declare(const EntitySyntax& entity);
		const SymbolTableEntry *findEntry(const QualifiedIdentifier& identifier, usize index) const;

	public:

		PackageSymbolTable(const PackageSyntax& syntax, const SymbolTable *parent);
		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;

		const EntitySyntax *resolve(const Identifier& identifier) const;
		const EntitySyntax *resolve(const QualifiedIdentifier& identifier) const;

		const auto& syntax() const { return _syntax; }
		const auto& symbols() const { return _symbols; }
		auto& symbols() { return _symbols; }
		const SymbolTable *getParent() const { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Package; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& symbols);

		friend class SymbolTableEntry;
	};
}

#endif
