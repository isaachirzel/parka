#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/StructSymbolTable.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	SymbolTableEntry::SymbolTableEntry(const EntitySyntaxId& entityId, const SymbolTable& parent) :
	_syntaxId(entityId)
	{
		switch (entityId.type())
		{
			case EntityType::Package:
				new (&_package) PackageSymbolTable(_syntaxId, &parent);
				break;

			case EntityType::Struct:
				new (&_struct) StructSymbolTable(_syntaxId, parent);
				break;

			default:
				break;
		}
	}

	SymbolTableEntry::SymbolTableEntry(SymbolTableEntry&& other) :
	_syntaxId(std::move(other._syntaxId))
	{
		// TODO: Implement for other table types
		switch (_syntaxId.type())
		{
			case EntityType::Package:
				new (&_package) auto(std::move(other._package));
				break;

			case EntityType::Struct:
				new (&_struct) auto(std::move(other._struct));
				break;

			default:
				break;
		}
	}

	SymbolTableEntry::~SymbolTableEntry()
	{
		switch (_syntaxId.type())
		{
			case EntityType::Package:
				_package.~PackageSymbolTable();
				break;

			case EntityType::Struct:
				_struct.~StructSymbolTable();
				break;

			default:
				break;
		}
	}

	void SymbolTableEntry::setParent(const SymbolTable& parent)
	{
		switch (_syntaxId.type())
		{
			case EntityType::Package:
				_package._parent = &parent;
				break;

			case EntityType::Struct:
				_struct._parent = &parent;
				break;

			default:
				break;
		}
	}

	// static std::ostream& scope(std::ostream& out, const SymbolTable *)
	// {
	// 	// if (symbolTable != nullptr)
	// 	// 	scope(out, symbolTable->getParent()) << "::" << symbolTable->;

	// 	return out;
	// }

	std::ostream& operator<<(std::ostream& out, const SymbolTableEntry& entry)
	{
		// const auto *symbolTable = entry.getSymbolTable();

		out << entry._syntaxId->identifier() << ":\t\t" << entry._syntaxId.type() << '\n';

		// TODO: Implement outputting tables

		return out;
	}
}
