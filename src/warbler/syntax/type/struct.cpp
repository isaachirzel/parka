#include <warbler/syntax/type/struct.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Struct::Struct(Identifier&& name, Array<Member>&& members) :
	_name(std::move(name)),
	_members(std::move(members))
	{}

	Result<Struct> Struct::parse(lexicon::Token& token, Identifier&& name)
	{
		if (token.next().type() != lexicon::TokenType::LeftBrace)
		{
			print_parse_error(token, "'{' before struct body");
			return {};
		}

		token.next();

		Array<Member> members;

		if (token.type() != lexicon::TokenType::RightBrace)
		{
			while (true)
			{
				auto member = Member::parse(token.next());

				if (!member)
					return {};

				members.emplace_back(member.unwrap());

				if (token.type() != lexicon::TokenType::Comma)
					break;

				token.next();
			}

			if (token.type() != lexicon::TokenType::RightBrace)
			{
				print_parse_error(token, "'}' after struct body");
				return {};
			}
		}

		token.next();

		return Struct { std::move(name), std::move(members) };
	}
	
	// bool Struct::validate(semantics::ModuleContext& mod_ctx)
	// {
	// 	for (auto& member : _members)
	// 	{
	// 		if (!member.validate(mod_ctx, _context))
	// 			return false;
	// 	}

	// 	return true;
	// }

	void Struct::print_tree(u32 depth) const
	{

		print_branch(depth, "struct");
		print_branch(depth, "{");

		for (const auto& member: _members)
			member.print_tree(depth + 1);

		print_branch(depth, "}");
	}
}