#ifndef WARBLER_AST_TYPENAME_HPP
#define WARBLER_AST_TYPENAME_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>

// no type
#define PRIMITIVE_VOID	0

// signed integers
#define PRIMITIVE_I8	1
#define PRIMITIVE_I16	2
#define PRIMITIVE_I32	3
#define PRIMITIVE_I64	4
#define PRIMITIVE_ISIZE	5

// unsigned integers
#define PRIMITIVE_U8	6
#define PRIMITIVE_U16	7
#define PRIMITIVE_U32	8
#define PRIMITIVE_U64	9
#define PRIMITIVE_USIZE	10

// binary types
#define PRIMITIVE_B8	11
#define PRIMITIVE_B16	12
#define PRIMITIVE_B32	13
#define PRIMITIVE_B64	14

// floating point types
#define PRIMITIVE_F32	15
#define PRIMITIVE_F64	16

// util types
#define PRIMITIVE_CHAR	17
#define PRIMITIVE_BOOL	18

namespace warbler::ast
{
	class Typename
	{
	public:

		static const Table<u32> primitive_types;
		static u32 generate_id();

	private:

		Location _location;
		String _name;
		u32 _id;
		u32 _reference_depth;

	public:

		Typename();
		Typename(const Location& location, String&& name);

		static Result<Typename> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		void print_tree(u32 depth = 0) const;
		bool validate();

		const Location& location() const { return _location; }
		const String& name() const { return _name; }
		u32 id() const { return _id; }
		u32 reference_depth() const { return _reference_depth; }
	};
}

#endif
