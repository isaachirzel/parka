#include <warbler/ast/parameter.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler
{
	Parameter::Parameter(Identifier&& name, Typename&& type) :
	_name(name),
	_type(type)
	{}

	static Result<Parameter> parse(TokenIterator& iter)
	{
		auto name = Identifier::parse(iter);

		if (name.has_error())
			return name.error();

		if (iter->type() != TOKEN_COLON)
		{
			errortf(*iter, "type specification is necessary for function parameters: %t", &(*iter));
			return ERROR_ARGUMENT;
		}

		iter += 1;

		auto type = Typename::parse(iter);

		if (type.has_error())
			return type.error();

		return Parameter(name.unwrap(), type.unwrap());
	}

	static Result<std::vector<Parameter>> parse_list(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_LPAREN)
		{
			errortf(*iter, "expected '(' at start of parameter list but got: %t", &(*iter));
			return ERROR_ARGUMENT;
		}

		iter += 1;

		std::vector<Parameter> out;

		if (iter->type() != TOKEN_RPAREN)
		{
			while(true)
			{
				auto res = Parameter::parse(iter);

				if (res.has_error())
					return res.error();

				out.emplace_back(res.unwrap());

				if (iter->type() == TOKEN_COMMA)
				{
					iter += 1;
					continue;
				}

				break;
			}

			if (iter->type() != TOKEN_RPAREN)
			{
				errortf(*iter, "expected ',' or ')' after parameter but got: %t", iter);
				return ERROR_ARGUMENT;
			}
		}

		iter += 1;

		return out;
	}

	void Parameter::print_tree(u32 depth) const
	{
		_name.print_tree(depth);
		_type.print_tree(depth + 1);
	}
}