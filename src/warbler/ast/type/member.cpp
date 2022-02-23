#include <warbler/ast/type/member.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler::ast
{
	Member::Member(Identifier&& name, Type&& type, bool is_public) :
	_name(std::move(name)),
	_type(std::move(type)),
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
			return {};

		if (iter->type() != TOKEN_COLON)
		{
			parse_error(iter, "':' after member name");
			return {};
		}
		
		iter += 1;

		auto type = Type::parse(iter);

		if (!type)
			return {};

		return Member(name.unwrap(), type.unwrap(), is_public);
	}

	bool Member::validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx)
	{
		auto *member = type_ctx.get_member(_name.text());

		if (member != nullptr)
		{
			print_error(_name.location(), "member '" + _name.text() + "' already defined in type '" + type_ctx.name + "'");
			print_note(member->name().location(), "previous declaration here");
			return false;
		}

		type_ctx.members[_name.text()] = this;

		return _type.validate(mod_ctx);
	}

	void Member::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth)
			<< (_is_public ? "public " : "private ")
			<< _name.text()
			<< ": " << _type.name() << '\n';
	}
}
