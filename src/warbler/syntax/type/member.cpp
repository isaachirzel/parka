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

	Result<Member> Member::parse(lexicon::Token& token)
	{
		auto is_public = false;

		if (token.type() == lexicon::TokenType::KeywordPublic)
		{
			is_public = true;
			token.next();
		}
		else if (token.type() == lexicon::TokenType::KeywordPrivate)
		{
			token.next();
		}

		auto name = Identifier::parse(token.next());

		if (!name)
			return {};

		if (token.type() != lexicon::TokenType::Colon)
		{
			print_parse_error(token, "':' after member name");
			return {};
		}
		
		token.next();

		auto type = Type::parse(token.next());

		if (!type)
			return {};

		return Member(name.unwrap(), type.unwrap(), is_public);
	}

	// bool Member::validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx)
	// {
	// 	auto *member = type_ctx.get_member(_name.token().text());

	// 	if (member != nullptr)
	// 	{
	// 		print_error(_name.token(), "member '" + _name.token().text() + "' already defined in type '" + type_ctx.name + "'");
	// 		print_note(member->name().token(), "previous declaration here");
	// 		return false;
	// 	}

	// 	type_ctx.members[_name.text()] = this;

	// 	return _type.validate(mod_ctx);
	// }

	// void Member::print_tree(u32 depth) const
	// {
	// 	print_branch(depth, (_is_public ? "public" : "private") + _name.token().text() + ": " + _type.base_type().text());
	// }
}
