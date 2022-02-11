#include <warbler/ast/typename.hpp>

// standard headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	static u32 last_type_id = PRIMITIVE_BOOL;

	u32 Typename::generate_id()
	{
		last_type_id += 1;

		return last_type_id;
	}

	const Table<u32> Typename::primitive_types =
	{
		// no type
		{ "void", PRIMITIVE_VOID },

		// signed types
		{ "i8", PRIMITIVE_I8 },
		{ "i16", PRIMITIVE_I16 },
		{ "i32", PRIMITIVE_I32 },
		{ "i64", PRIMITIVE_I64 },
		{ "isize", PRIMITIVE_ISIZE },

		// unsigned types
		{ "u8", PRIMITIVE_U8 },
		{ "u16", PRIMITIVE_U16 },
		{ "u32", PRIMITIVE_U32 },
		{ "u64", PRIMITIVE_U64 },
		{ "usize", PRIMITIVE_USIZE },

		// binary types
		{ "b8", PRIMITIVE_B8 },
		{ "b16", PRIMITIVE_B16 },
		{ "b32", PRIMITIVE_B32 },
		{ "b64", PRIMITIVE_B64 },

		// floating point types
		{ "f32", PRIMITIVE_F32 },
		{ "f64", PRIMITIVE_F64 },

		// util types
		{ "char", PRIMITIVE_CHAR },
		{ "bool", PRIMITIVE_BOOL },
	};

	Typename::Typename(const Location& location) :
	_location(location),
	_name("void"),
	_id(PRIMITIVE_VOID)
	{}

	Typename::Typename(const Location& location, String&& name) :
	_location(location),
	_name(std::move(name)),
	_id(PRIMITIVE_VOID)
	{}

	Result<Typename> Typename::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			error_out(iter) << "expected typename but got: " << *iter << std::endl;
			return ERROR_ARGUMENT;
		}
		
		const auto& location = iter->location();
		String name = String(location.pos_ptr(), location.length());

		iter += 1;

		return Typename(location, std::move(name));
	}

	bool Typename::validate(semantics::Context& context)
	{
		if (context.types.find(_name) == context.types.end() && primitive_types.find(_name) == primitive_types.end())
		{
			error_out(_location) << '\'' << _name << "' is not an imported or locally defined type or primitive";
			error_highlight(_location);
			return false;
		}

		return true;
	}

	void Typename::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << (_id == 0 ? "<auto>" : _name) << '\n';
	}
}