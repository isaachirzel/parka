#ifndef WARBLER_AST_SEMANTICS_CONTEXT_HPP
#define WARBLER_AST_SEMANTICS_CONTEXT_HPP

// local headers
#include <warbler/util/table.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/set.hpp>

// forward declarations

namespace warbler::ast
{
	class TypeDefinition;
	class Parameter;
	class Declaration;
	class Function;
}

namespace warbler::semantics
{
	struct ModuleContext
	{
		String module_name;
		Table<ast::TypeDefinition*> types;
		Table<ast::Function*> functions;
	};

	struct FunctionContext
	{
		Table<ast::Declaration*> variables;
		Table<ast::Parameter*> parameters;
	};
}

#endif
