#include <warbler/syntax/type/member.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Member::Member(Identifier&& name, Type&& type, bool is_public) :
	_name(std::move(name)),
	_type(std::move(type)),
	_is_public(is_public)
	{}

	Result<Member> Member::parse(lexicon::TokenIterator& iter)
	{
		auto is_public = false;

		if (iter->type() == lexicon::TokenType::KeywordPublic)
		{
			is_public = true;
			iter += 1;
		}
		else if (iter->type() == lexicon::TokenType::KeywordPrivate)
		{
			iter += 1;
		}

		auto name = Identifier::parse(iter);

		if (!name)
			return {};

		if (iter->type() != lexicon::TokenType::Colon)
		{
			print_parse_error(iter, "':' after member name");
			return {};
		}
		
		iter += 1;

		auto type = Type::parse(iter);

		if (!type)
			return {};

		return Member(name.unwrap(), type.unwrap(), is_public);
	}

	// bool Member::validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx)
	// {
	// 	auto *member = type_ctx.get_member(_name.location().text());

	// 	if (member != nullptr)
	// 	{
	// 		print_error(_name.location(), "member '" + _name.location().text() + "' already defined in type '" + type_ctx.name + "'");
	// 		print_note(member->name().location(), "previous declaration here");
	// 		return false;
	// 	}

	// 	type_ctx.members[_name.text()] = this;

	// 	return _type.validate(mod_ctx);
	// }

	void Member::print_tree(u32 depth) const
	{
		print_branch(depth, (_is_public ? "public" : "private") + _name.location().text() + ": " + _type.base_type().text());
	}
}
