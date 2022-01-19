#include <warbler/ast/typename.hpp>

// standard headers
#include <warbler/print.hpp>

namespace warbler
{
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
		
		String name = String(iter->text());

		const auto& location = iter->location();

		iter += 1;

		return Typename(location, std::move(name));
	}

	void Typename::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);
		std::cout << ": ";
		std::cout << (_id == 0 ? "<auto>" : _name);
		std::cout << '\n';
	}
}