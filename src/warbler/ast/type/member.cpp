#include <warbler/ast/type/member.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	Member::Member(Identifier&& name, Typename&& type, bool is_public) :
	_name(name),
	_type(type),
	_is_public(is_public)
	{}

	Result<Member> Member::parse(TokenIterator& iter)
	{
		auto is_public = false;

		if (iter->type() == TOKEN_PUBLIC)
		{
			is_public = true;
			iter += 1;
		}
		else if (iter->type() == TOKEN_PRIVATE)
		{
			iter += 1;
		}

		auto name = Identifier::parse(iter);

		if (!name)
			return name.error();

		if (iter->type() != TOKEN_COLON)
		{
			parse_error(iter, "':' after member name");
			return ERROR_ARGUMENT;
		}
		
		iter += 1;

		auto type = Typename::parse(iter);

		if (!type)
			return type.error();

		return Member(name.unwrap(), type.unwrap(), is_public);
	}

	bool Member::validate(semantics::ModuleContext& context)
	{
		return _type.validate(context);
	}

	void Member::print_tree(u32 depth) const
	{
		_name.print_tree(depth);

		if (_is_public)
		{
			std::cout << tree_branch(depth + 1) << "public\n";
		}
		else
		{
			std::cout << tree_branch(depth + 1) << "private\n";
		}

		_name.print_tree(depth + 1);
	}
}
