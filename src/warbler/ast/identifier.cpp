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
			error_out(iter) << "expected identifier but got: '" << *iter << '\''  << token_error(iter) << std::endl;
			return ERROR_ARGUMENT;
		}

		String text = String(iter->text());
			
		iter += 1;

		return Identifier(std::move(text));
	}

	void Identifier::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
	}
}