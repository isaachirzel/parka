#ifndef PARKA_SYMBOL_STRUCT_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_STRUCT_SYMBOL_TABLE_HPP

#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/MemberSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/util/Table.hpp"

// TODO: Figure out what to do here. Perhaps add member to entity list
namespace parka
{
	class StructSymbolTable : public SymbolTable
	{
		SymbolTable *_parent;
		StructSyntax& _syntax;
		Table<String, MemberSyntax*> _symbols;

	public:

		StructSymbolTable(StructSyntax& syntax, SymbolTable& parent);
		StructSymbolTable(StructSymbolTable&&) = default;
		StructSymbolTable(const StructSymbolTable&) = delete;

		EntitySyntax *resolve(const Identifier& identifier);
		EntitySyntax *resolve(const QualifiedIdentifier& identifier);
		
		SymbolTable *parent() { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Struct; }

		friend class SymbolTableEntry;
	};
}

#endif
