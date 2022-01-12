#include <warbler/ast/identifier.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler
{
	Identifier::Identifier(String&& text) :
	_text(text)
	{}

	Result<Identifier> Identifier::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			errortf(*iter, "expected identifier but got: %t", iter);
			return ERROR_ARGUMENT;
		}

		String text = String(iter->text());
			
		iter += 1;

		return Identifier(std::move(text));
	}

	void Identifier::print_tree(u32 depth) const
	{
		print_branch(depth);
		puts(_text.c_str());
	}
}