#include <warbler/ast/typename.hpp>

// standard headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	Typename::Typename() :
	_location(),
	_name("")
	{}

	Typename::Typename(const Location& location, String&& name) :
	_location(location),
	_name(std::move(name))
	{}

	Result<Typename> Typename::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			error_out(iter) << "expected typename but got: " << *iter << std::endl;
			return {};
		}
		
		const auto& location = iter->location();
		String name = String(location.pos_ptr(), location.length());

		iter += 1;

		return Typename(location, std::move(name));
	}

	bool Typename::validate(semantics::ModuleContext& context)
	{
		if (context.types.find(_name) == context.types.end() && context.primitives.find(_name) == context.primitives.end())
		{
			print_error(_location, "'" + _name + "' is not an imported or locally defined type");
			return false;
		}

		return true;
	}

	void Typename::print_tree(u32 depth) const
	{
		
		std::cout << tree_branch(depth) << ": " <<  _name << '\n';
	}
}