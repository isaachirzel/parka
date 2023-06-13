#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/log/Log.hpp"
#include <iomanip>

namespace parka
{
	SymbolTableEntry::SymbolTableEntry(const EntitySyntax& syntax, SymbolTable& parent) :
	_syntax(syntax),
	_context(nullptr)
	{}

	void SymbolTableEntry::setParent(SymbolTable& parent)
	{
		switch (_syntax.entityType())
		{
			// case EntityType::Package:
			// 	_package._parent = &parent;
			// 	break;

			// case EntityType::Struct:
			// 	_struct._parent = &parent;
			// 	break;

			default:
				break;
		}

		log::fatal("Unable to set parent of Entity with Type: $", _syntax.entityType());
	}

	void SymbolTableEntry::setContext(const EntityContext& context)
	{
		assert(_context == nullptr);
		assert(context.entityType() == _syntax.entityType());

		_context = &context;
	}

	std::ostream& operator<<(std::ostream& out, const SymbolTableEntry& entry)
	{
		out << entry._syntax.identifier() << ": " << entry._syntax.entityType();
		
		if (entry._context != nullptr)
			out << " [validated]";

		return out;
	}
}
