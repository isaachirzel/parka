#ifndef WARBLER_SYNTAX_TYPE_PRIMITIVE_HPP
#define WARBLER_SYNTAX_TYPE_PRIMITIVE_HPP

#include <warbler/util/primitive.hpp>
#include <warbler/syntax/identifier.hpp>
#include <warbler/syntax/type/type_definition.hpp>
#include <warbler/syntax/type/member.hpp>

namespace warbler::syntax
{
	enum class PrimitiveType
	{
		Integer,
		Unsigned,
		Binary,
		Float,
		Bool,
		Char,
		Str
	};

	class Primitive : public TypeDefinition
	{
	private:

		Identifier _name;
		u32 _bytes;
		PrimitiveType _type;

	public:

		Primitive(Identifier&& name, u32 bytes, PrimitiveType type);

		
		void print_tree(u32 depth = 0) const;

		Member *get_member(const String&) { return nullptr; }
		bool is_primitive() const { return true; }
		const Identifier& name() const { return _name; }
		u32 bytes() const { return _bytes; }
		PrimitiveType type() const { return _type; }
	};
}

#endif
