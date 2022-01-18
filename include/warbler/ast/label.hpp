#ifndef WARBLER_AST_LABEL_HPP
#define WARBLER_AST_LABEL_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/result.hpp>

namespace warbler
{
	class Label
	{
	private:

		String _identifier;

	public:

		Label(String&& identifier);

		static Result<Label> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
