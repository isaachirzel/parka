#include "parka/symbol/StructSymbolTable.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include <cassert>

namespace parka
{
	StructSymbolTable::StructSymbolTable(const StructSyntax& syntax, const SymbolTable& parent) :
	_syntax(syntax),
	_parent(&parent)
	{
		for (const auto& memberSyntax : syntax.members())
		{
			// TODO: Implement member ids
			assert(!memberSyntax.symbol().empty());
		}
	}

	EntitySyntax *StructSymbolTable::resolve(const Identifier& identifier) const
	{
		log::notImplemented(here());
	}

	EntitySyntax *StructSymbolTable::resolve(const QualifiedIdentifier& identifier) const
	{
		log::notImplemented(here());
	}
}