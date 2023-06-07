#ifndef PARKA_SYMBOL_STRUCT_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_STRUCT_SYMBOL_TABLE_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Table.hpp"

// TODO: Figure out what to do here. Perhaps add member to entity list
namespace parka
{
	class StructSymbolTable : public SymbolTable
	{
		EntitySyntaxId _syntaxId;
		const SymbolTable *_parent;
		Table<String, EntitySyntaxId> _symbols;

		StructSymbolTable(const EntitySyntaxId& syntaxId, const SymbolTable& parent);

	public:

		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		
		const SymbolTable *getParent() const { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Struct; }

		friend class SymbolTableEntry;
	};
}

#endif
