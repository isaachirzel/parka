#include <warbler/ast/label.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler
{
	Label::Label(String&& identifier) :
	_identifier(identifier)
	{}

	Result<Label> Label::parse(TokenIterator& iter)
	{

		if (iter->type() != TOKEN_IDENTIFIER)
		{
			error_out(iter) << "expected identifier for label but got: " << *iter << std::endl;
			return ERROR_ARGUMENT;
		}

		String identifier = String(iter->text());

		iter += 1;

		if (iter->type() != TOKEN_COLON)
		{
			error_out(iter) << "expected ':' after label but got: " << *iter << std::endl;
			return ERROR_ARGUMENT;
		}

		iter += 1;

		return Label(std::move(identifier));
	}

	void Label::print_tree(u32 depth) const
	{
		print_branch(depth);
		puts(_identifier.c_str());
	}
}
