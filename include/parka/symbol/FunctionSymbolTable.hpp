#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class PackageSymbolTable;

	class FunctionSymbolTable
	{
		EntitySyntaxId _functionId;
		const PackageSymbolTable& _parentPackage;
		Table<String, EntitySyntaxId> _symbols;
		Array<BlockSymbolTable> _blocks;

	public:

		FunctionSymbolTable(const EntitySyntaxId& functionId, const PackageSymbolTable& parentPackage) :
		_functionId(functionId),
		_parentPackage(parentPackage)
		{}

		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		
		void addBlock(const ExpressionSyntaxId& blockId);
	};
}

#endif

