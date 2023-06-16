#ifndef PARKA_AST_ENTITY_HPP
#define PARKA_AST_ENTITY_HPP

#include "parka/ir/Entity.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"

namespace parka::ast
{
	// TODO: Make entityType a data member
	struct EntityAst : public SymbolTableEntry
	{
		virtual ~EntityAst() {}
		virtual EntityType entityType() const = 0;
		virtual const Identifier& identifier() const = 0;
		virtual const String& name() const = 0;
		virtual ir::EntityIr *context() = 0;

		friend std::ostream& operator<<(std::ostream& out, const EntityAst& syntax);
	};
}

#endif
