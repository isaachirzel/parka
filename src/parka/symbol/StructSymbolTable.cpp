#include "parka/symbol/StructSymbolTable.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include <cassert>

namespace parka
{
	StructSymbolTable::StructSymbolTable(const EntitySyntaxId& syntaxId, const SymbolTable& parent) :
	_syntaxId(syntaxId),
	_parent(&parent)
	{
		const auto& syntax = syntaxId.getStruct();

		for (const auto& memberSyntax : syntax.members())
		{
			// TODO: Implement member ids
			assert(!memberSyntax.symbol().empty());
		}
	}

	Optional<EntitySyntaxId> StructSymbolTable::resolve(const Identifier& identifier) const
	{
		log::notImplemented(here());
	}

	Optional<EntitySyntaxId> StructSymbolTable::resolve(const QualifiedIdentifier& identifier) const
	{
		log::notImplemented(here());
	}
}