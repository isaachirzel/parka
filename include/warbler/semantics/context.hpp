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
		String name;
		Table<ast::Declaration*> variables;
		Table<ast::Parameter*> parameters;

		bool contains_parameter(const String& name)
		{
			return parameters.find(name) != parameters.end();
		}

		bool contains_variable(const String& name)
		{
			return variables.find(name) != variables.end();
		}

		bool contains_name(const String& name)
		{
			return contains_parameter(name) || contains_variable(name);
		}
	};
}

#endif
