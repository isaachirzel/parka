#include <warbler/ast/identifier.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler::ast
{
	Identifier::Identifier(const Location& location, String&& text) :
	_location(location),
	_text(text)
	{}

	Result<Identifier> Identifier::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			parse_error(iter, "identifier");
			return ERROR_ARGUMENT;
		}

		const auto& location = iter->location();
		String text = String(location.pos_ptr(), location.length());

		iter += 1;

		return Identifier(location, std::move(text));
	}

	void Identifier::validate(semantics::Context& context)
	{
		usize size = 0;

		for (const auto& scope : context.scope)
			size += scope.size() + 1;

		_symbol.reserve(size);

		bool is_first = true;

		for (const auto& scope : context.scope)
		{
			if (is_first)
			{
				is_first = false;
			}
			else
			{
				_symbol += '$';
			}

			_symbol += scope;
		}
	}

	void Identifier::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
	}
}