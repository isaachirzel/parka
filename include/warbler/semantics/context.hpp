#ifndef WARBLER_AST_SEMANTICS_CONTEXT_HPP
#define WARBLER_AST_SEMANTICS_CONTEXT_HPP

// local headers
#include <warbler/util/table.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/string.hpp>
#include <warbler/semantics/symbol.hpp>

namespace warbler::semantics
{
	struct Context
	{
		Table<u32> types;
		Table<Symbol> symbols;
	};
}

#endif
