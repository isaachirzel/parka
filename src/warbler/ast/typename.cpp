#include <warbler/ast/typename.hpp>

// standard headers
#include <warbler/print.hpp>

namespace warbler
{
	Typename::Typename(String&& name) :
	_name(name)
	{}

	Result<Typename> Typename::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			errortf(*iter, "expected typename but got: %t", &(*iter));
			return ERROR_ARGUMENT;
		}
		
		String name = String(iter->text());

		iter += 1;

		return Typename(std::move(name));
	}

	void Typename::print_tree(u32 depth) const
	{
		print_branch(depth);
		puts(_name.c_str());
	}
}