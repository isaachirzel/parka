#ifndef WARBLER_AST_SEMANTICS_CONTEXT_HPP
#define WARBLER_AST_SEMANTICS_CONTEXT_HPP

// local headers
#include <warbler/util/table.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/set.hpp>

// standard headers
#include <cassert>

// forward declarations

namespace warbler::ast
{
	class TypeDefinition;
	class Member;

	class Function;
	class Declaration;
}

namespace warbler::semantics
{
	struct ModuleContext
	{
		String name;
		Table<ast::TypeDefinition*> types;
		Table<ast::Function*> functions;

		ast::TypeDefinition *get_type(const String& name);
		ast::Function *get_function(const String& name);
	};
	
	struct TypeContext
	{
		String name;
		Table<ast::Member*> members;

		ast::Member *get_member(const String& name);
	};

	struct BlockContext
	{
		Table<ast::Declaration*> variables;

		ast::Declaration *get_variable(const String& name);
	};


	struct FunctionContext
	{
		String name;
		Table<ast::Declaration*> parameters;
		Array<BlockContext*> blocks;

		ast::Declaration *get_parameter(const String& name);
		ast::Declaration *get_declaration(const String& name);
		ast::Declaration *get_declaration_in_current_block(const String& name);

		bool is_body_scope() const { return blocks.size() == 1; }
		BlockContext& current_block() const { return *blocks.back(); }
	};

	void init_context();
}

#endif
