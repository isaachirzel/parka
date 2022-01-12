#ifndef WARBLER_AST_TYPENAME_HPP
#define WARBLER_AST_TYPENAME_HPP

// local headers
#include <warbler/result.hpp>
#include <warbler/token.hpp>
#include <warbler/primitive.hpp>

namespace warbler
{
	class Typename
	{
	private:

		String _name;

	public:

		Typename();
		Typename(String&& name);

		static Result<Typename> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
