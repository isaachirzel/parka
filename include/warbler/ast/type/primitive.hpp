#ifndef WARBLER_AST_TYPE_PRIMITIVE_HPP
#define WARBLER_AST_TYPE_PRIMITIVE_HPP

#include <warbler/util/primitive.hpp>
#include <warbler/ast/type/type_definition.hpp>

namespace warbler::ast
{
	enum PrimitiveType
	{
		PRIMITIVE_INTEGER,
		PRIMITIVE_UNSIGNED,
		PRIMITIVE_BINARY,
		PRIMITIVE_FLOAT,
		PRIMITIVE_BOOL,
		PRIMITIVE_CHAR,
		PRIMITIVE_STR
	};

	class Primitive : public TypeDefinition
	{
	private:

		Identifier _name;
		u32 _bytes;
		PrimitiveType _type;

	public:

		Primitive(Identifier&& name, u32 bytes, PrimitiveType type);

		bool validate(semantics::ModuleContext& mod_ctx);
		void print_tree(u32 depth = 0) const;

		Member *get_member(const String&) { return nullptr; }
		bool is_primitive() const { return true; }
		const Identifier& name() const { return _name; }
	};
}

#endif
