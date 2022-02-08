#ifndef WARBLER_AST_TYPE_ENUM_HPP
#define WARBLER_AST_TYPE_ENUM_HPP

// local headers
#include <warbler/ast/identifier.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Enum
	{
	private:

		Array<Identifier> _values;

	public:

		Enum(Array<Identifier>&& values);

		static Result<Enum> parse(TokenIterator& iter);

		bool validate(semantics::Context& context);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
