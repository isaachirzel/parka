#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/StructSymbolTable.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	SymbolTableEntry::SymbolTableEntry(const EntitySyntax& syntax, const SymbolTable& parent) :
	_syntax(syntax)
	{
		switch (syntax.type())
		{
			case EntityType::Package:
				new (&_package) PackageSymbolTable((PackageSyntax&)_syntax, &parent);
				break;

			case EntityType::Struct:
				new (&_struct) StructSymbolTable((StructSyntax&)_syntax, parent);
				break;

			default:
				break;
		}
	}

	SymbolTableEntry::SymbolTableEntry(SymbolTableEntry&& other) :
	_syntax(other._syntax),
	_context(other._context)
	{
		// TODO: Implement for other table types
		switch (_syntax.type())
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
		switch (_syntax.type())
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
		switch (_syntax.type())
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

		out << entry._syntax.identifier() << ":\t\t" << entry._syntax.type();
		
		if (entry._context != nullptr)
			out << " [validated]";

		out << '\n';

		// TODO: Implement outputting tables

		return out;
	}
}
