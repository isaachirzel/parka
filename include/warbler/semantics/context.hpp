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
		String name;
		Table<ast::TypeDefinition*> types;
		Table<ast::Function*> functions;
	};

	struct BlockContext
	{
		Table<ast::Declaration*> variables;

		bool contains(const String& name)
		{
			return variables.find(name) != variables.end();
		}
	};

	struct FunctionContext
	{
		String name;
		Table<ast::Parameter*> parameters;
		Array<BlockContext*> blocks;

		bool contains(const String& name)
		{
			return parameters.find(name) != parameters.end();
		}
	};
}

#endif
