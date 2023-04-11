#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class PackageSymbolTable;

	class FunctionSymbolTable
	{
		EntityId _functionId;
		const PackageSymbolTable& _parentPackage;
		Table<String, EntityId> _symbols;
		Array<BlockSymbolTable> _blocks;

	public:

		FunctionSymbolTable(const EntityId& functionId, const PackageSymbolTable& parentPackage) :
		_functionId(functionId),
		_parentPackage(parentPackage)
		{}

		Optional<EntityId> resolve(const Identifier& identifier) const;
		Optional<EntityId> resolve(const QualifiedIdentifier& identifier) const;
		
		void addBlock(const ExpressionId& blockId);
	};
}

#endif

