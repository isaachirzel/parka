#ifndef WARBLER_AST_IDENTIFIER_HPP
#define WARBLER_AST_IDENTIFIER_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>

// standard headers
#include <string>

namespace warbler
{
	class Identifier
	{
	private:

		String _text;

	public:

		Identifier() = delete;
		Identifier(String&& text);

		static Result<Identifier> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;

		const String& text() const { return _text; }
	};

}
#endif
