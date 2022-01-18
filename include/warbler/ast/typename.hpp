#ifndef WARBLER_AST_TYPENAME_HPP
#define WARBLER_AST_TYPENAME_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>

namespace warbler
{
	class Typename
	{
	private:

		String _name;
		u32 _id;

	public:

		Typename();
		Typename(String&& name);

		static Result<Typename> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
