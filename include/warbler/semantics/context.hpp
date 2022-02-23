#ifndef WARBLER_SYNTAX_SEMANTICS_CONTEXT_HPP
#define WARBLER_SYNTAX_SEMANTICS_CONTEXT_HPP

// local headers
#include <warbler/util/table.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/set.hpp>

// standard headers
#include <cassert>

// forward declarations

namespace warbler::syntax
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
		Table<syntax::TypeDefinition*> types;
		Table<syntax::Function*> functions;

		syntax::TypeDefinition *get_type(const String& name);
		syntax::Function *get_function(const String& name);
	};
	
	struct TypeContext
	{
		String name;
		Table<syntax::Member*> members;

		syntax::Member *get_member(const String& name);
	};

	struct BlockContext
	{
		Table<syntax::Declaration*> variables;

		syntax::Declaration *get_variable(const String& name);
	};


	struct FunctionContext
	{
		String name;
		Table<syntax::Declaration*> parameters;
		Array<BlockContext*> blocks;

		syntax::Declaration *get_parameter(const String& name);
		syntax::Declaration *get_declaration(const String& name);
		syntax::Declaration *get_declaration_in_current_block(const String& name);

		bool is_body_scope() const { return blocks.size() == 1; }
		BlockContext& current_block() const { return *blocks.back(); }
	};

	void init_context();
}

#endif
