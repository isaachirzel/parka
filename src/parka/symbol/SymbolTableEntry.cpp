#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	SymbolTableEntry::SymbolTableEntry(const EntitySyntaxId& entityId, const SymbolTable& parent) :
	_entityId(entityId),
	_type(entityId->type())
	{
		switch (_type)
		{
			case EntityType::Package:
				assert(parent.symbolTableType() == SymbolTableType::Package);
				new (&_package) PackageSymbolTable(_entityId, (const PackageSymbolTable&)parent);
				break;

			case EntityType::Function:
				assert(parent.symbolTableType() == SymbolTableType::Function);
				new (&_function) FunctionSymbolTable(_entityId, parent);
				break;

			default:
				break;
		}
	}
}
