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
				new (&_package) PackageSymbolTable(_entityId, parent);
				break;

			case EntityType::Function:
				new (&_function) FunctionSymbolTable(_entityId, parent);
				break;

			default:
				break;
		}
	}

	SymbolTableEntry::SymbolTableEntry(SymbolTableEntry&& other) :
	_entityId(std::move(other._entityId)),
	_type(other._type)
	{
		// TODO: Implement for other table types
		switch (_type)
		{
			case EntityType::Function:
				new (&_function) auto(std::move(other._function));
				break;

			case EntityType::Package:
				new (&_package) auto(std::move(other._package));
				break;

			default:
				break;
		}
	}

	SymbolTableEntry::~SymbolTableEntry()
	{
		switch (_type)
		{
			case EntityType::Function:
				_function.~FunctionSymbolTable();
				break;

			case EntityType::Package:
				_package.~PackageSymbolTable();
				break;

			default:
				break;
		}
	}

	void SymbolTableEntry::setParent(const SymbolTable& parent)
	{
		switch (_type)
		{
			case EntityType::Function:
				_function._parent = &parent;
				break;

			case EntityType::Package:
				_package._parent = &parent;
				break;

			default:
				break;
		}
	}
}