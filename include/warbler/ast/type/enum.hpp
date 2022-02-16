#ifndef WARBLER_AST_TYPE_ENUM_HPP
#define WARBLER_AST_TYPE_ENUM_HPP

// local headers
#include <warbler/ast/type/type.hpp>

namespace warbler::ast
{
	class Enum : public Type
	{
	private:

		Array<Member> _values;

	public:

		Enum(Array<Member>&& values);

		static Result<Enum> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
