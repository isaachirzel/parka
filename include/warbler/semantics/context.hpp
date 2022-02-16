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
	class Type;
	class Member;

	class Function;
	class Declaration;
}

namespace warbler::semantics
{
	enum PrimitiveType
	{
		PRIMIIVE_NONE,

		PRIMITIVE_I8,
		PRIMITIVE_I16,
		PRIMITIVE_I32,
		PRIMITIVE_I64,
		PRIMITIVE_ISIZE,

		PRIMITIVE_U8,
		PRIMITIVE_U16,
		PRIMITIVE_U32,
		PRIMITIVE_U64,
		PRIMITIVE_USIZE,

		PRIMITIVE_B8,
		PRIMITIVE_B16,
		PRIMITIVE_B32,
		PRIMITIVE_B64,

		PRIMITIVE_F32,
		PRIMITIVE_F64,

		PRIMITIVE_CHAR,
		PRIMITIVE_BOOL,
		PRIMITIVE_STR
	};

	struct ModuleContext
	{
		String name;
		Table<ast::Type*> types;
		static const Table<PrimitiveType> primitives;
		Table<ast::Function*> functions;

		ast::Type *get_type(const String& name);
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
		BlockContext *body;
		Array<BlockContext*> blocks;

		ast::Declaration *get_parameter(const String& name);
		ast::Declaration *get_declaration(const String& name);
		ast::Declaration *get_declaration_in_current_block(const String& name);

		bool is_body_scope() const { return blocks.empty(); }
		BlockContext& current_block() const { return blocks.empty() ? *body : *blocks.back(); }
	};
}

#endif
