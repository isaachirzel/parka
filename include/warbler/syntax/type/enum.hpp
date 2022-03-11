#ifndef WARBLER_SYNTAX_TYPE_ENUM_HPP
#define WARBLER_SYNTAX_TYPE_ENUM_HPP

// local headers
#include <warbler/syntax/type/type_definition.hpp>

namespace warbler::syntax
{
	class Enum : public Type
	{
	private:

		Array<Member> _values;

	public:

		Enum(Array<Member>&& values);

		static Result<Enum> parse(lexicon::Token& token);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
