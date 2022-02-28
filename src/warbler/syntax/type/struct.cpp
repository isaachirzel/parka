#include <warbler/syntax/type/struct.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Struct::Struct(Identifier&& name, Array<Member>&& members) :
	_name(std::move(name)),
	_members(std::move(members))
	{}

	Result<Struct> Struct::parse(lexicon::TokenIterator& iter, Identifier&& name)
	{
		iter += 1;

		if (iter->type() != lexicon::TokenType::LeftBrace)
		{
			print_parse_error(iter, "'{' before struct body");
			return {};
		}

		iter += 1;

		Array<Member> members;

		if (iter->type() != lexicon::TokenType::RightBrace)
		{
			while (true)
			{
				auto member = Member::parse(iter);

				if (!member)
					return {};

				members.emplace_back(member.unwrap());

				if (iter->type() != lexicon::TokenType::Comma)
					break;

				iter += 1;
			}

			if (iter->type() != lexicon::TokenType::RightBrace)
			{
				print_parse_error(iter, "'}' after struct body");
				return {};
			}
		}

		iter += 1;

		return Struct { std::move(name), std::move(members) };
	}
	
	bool Struct::validate(semantics::ModuleContext& mod_ctx)
	{
		for (auto& member : _members)
		{
			if (!member.validate(mod_ctx, _context))
				return false;
		}

		return true;
	}

	void Struct::print_tree(u32 depth) const
	{

		print_branch(depth, "struct");
		print_branch(depth, "{");

		for (const auto& member: _members)
			member.print_tree(depth + 1);

		print_branch(depth, "}");
	}
}