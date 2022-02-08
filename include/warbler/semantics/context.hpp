#ifndef WARBLER_AST_SEMANTICS_CONTEXT_HPP
#define WARBLER_AST_SEMANTICS_CONTEXT_HPP

// local headers
#include <warbler/util/table.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/set.hpp>

namespace warbler::semantics
{
	struct Context
	{
		Set<String> types;
		Set<String> symbols;
		Array<String> scope;

		String qualified_scope() const;
		String qualified_scope(const String& name) const;
		static u32 generate_type_id();
	};

}

#endif
