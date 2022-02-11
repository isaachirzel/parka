#include <warbler/ast/declaration.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Declaration::Declaration(bool is_mutable, Identifier&& name, Typename&& type) :
	_is_mutable(is_mutable),
	_name(std::move(name)),
	_type(std::move(type))
	{}

	Result<Declaration> Declaration::parse(TokenIterator& iter)
	{
		auto is_mutable = false;

		if (iter->type() == TOKEN_MUT)
		{
			is_mutable = true;
			iter += 1;
		}

		auto name = Identifier::parse(iter);
		
		if (name.has_error())
			return name.error();

		auto type = Typename(iter->location());

		if (iter->type() == TOKEN_COLON)
		{
			iter += 1;

			auto res = Typename::parse(iter);

			if (!res)
				return res.error();

			type = res.unwrap();
		}

		return Declaration { is_mutable, name.unwrap(), std::move(type) };
	}

	bool Declaration::validate(semantics::ModuleContext& module_context, semantics::FunctionContext& function_context)
	{
		
	}

	void Declaration::print_tree(u32 depth = 0) const
	{
		if (_is_mutable)
			std::cout << tree_branch(dept) << "mut\n";
	}
}
