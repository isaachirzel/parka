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
	class Typename;
	class Parameter;
	class Declaration;
	class Function;

	struct ModuleContext
	{
		String module_name;
		Table<Typename*> types;
		Table<Function*> functions;
	};

	struct Pointer
	{

	};

	struct Variable
	{
		Typename *type;


		u32 type_id;
		u16 reference_count;
		bool is_mutable;
		bool is_ref_mutable;
	};

	struct FunctionContext
	{
		Table<Declaration*> variables;
		Table<Parameter*> parameters;
	};
}

#endif
