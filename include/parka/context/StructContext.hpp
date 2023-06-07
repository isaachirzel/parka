#ifndef PARKA_CONTEXT_STRUCT_cONTEXT_HPP
#define PARKA_CONTEXT_STRUCT_cONTEXT_HPP

#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/StructSymbolTable.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class StructContext : public EntityContext
	{
		StructContext()
		{}

	public:
		StructContext(StructContext&&) = default;
		StructContext(const StructContext&) = delete;

		static Optional<EntityContextId> validate(StructSymbolTable& symbolTable);
		
		EntityType type() const { return EntityType::Struct; }
	};
}

#endif