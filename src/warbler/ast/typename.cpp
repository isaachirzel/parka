#include <warbler/ast/typename.hpp>

// standard headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	static std::unordered_set<String> primitive_types = {

		// signed types
		"i8",
		"i16",
		"i32",
		"i64",
		"isize",

		// unsigned types
		"u8",
		"u16",
		"u32",
		"u64",
		"usize",

		// floating point types
		"f32",
		"f64",

		// util types
		"char",
		"bool",
		"byte"
	};

	Typename::Typename() :
	_location(),
	_name(),
	_id(0)
	{}

	Typename::Typename(const Location& location, String&& name) :
	_location(location),
	_name(name),
	_id(1)
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