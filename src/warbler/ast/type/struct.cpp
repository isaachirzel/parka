#include <warbler/ast/type/struct.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Struct::Struct(Array<Member>&& members) :
	_members(std::move(members))
	{}

	Result<Struct> Struct::parse(TokenIterator& iter)
	{
		iter += 1;

		if (iter->type() != TOKEN_LBRACE)
		{
			parse_error(iter, "'{' before struct body");
			return {};
		}

		iter += 1;

		Array<Member> out;

		if (iter->type() != TOKEN_RBRACE)
		{
			while (true)
			{
				auto member = Member::parse(iter);

				if (!member)
					return {};

				out.emplace_back(member.unwrap());

				if (iter->type() != TOKEN_COMMA)
					break;

				iter += 1;
			}

			if (iter->type() != TOKEN_RBRACE)
			{
				parse_error(iter, "'}' after struct body");
				return {};
			}
		}

		iter += 1;

		return Struct { std::move(out) };
	}
	
	bool Struct::validate(semantics::ModuleContext& mod_ctx, semantics::TypeContext& type_ctx)
	{
		for (auto& member : _members)
		{
			if (!member.validate(mod_ctx, type_ctx))
				return false;
		}

		return true;
	}

	void Struct::print_tree(u32 depth) const
	{

		std::cout << tree_branch(depth) << "struct\n";
		std::cout << tree_branch(depth) << "{\n";

		for (const auto& member: _members)
			member.print_tree(depth + 1);

		std::cout << tree_branch(depth) << "}\n";
	}
}