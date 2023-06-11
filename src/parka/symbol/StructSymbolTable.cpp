#include "parka/symbol/StructSymbolTable.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include <cassert>

namespace parka
{
	StructSymbolTable::StructSymbolTable(StructSyntax& syntax, SymbolTable& parent) :
	_parent(&parent),
	_syntax(syntax),
	_symbols()
	{
		for (const auto& memberSyntax : syntax.members())
		{
			// TODO: Implement member ids
			assert(!memberSyntax.symbol().empty());
		}
	}

	const EntityContext *StructSymbolTable::resolve(const Identifier& identifier)
	{
		log::notImplemented(here());
	}

	const EntityContext *StructSymbolTable::resolve(const QualifiedIdentifier& identifier)
	{
		log::notImplemented(here());
	}
}