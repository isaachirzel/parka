#ifndef WARBLER_SYNTAX_TYPE_MEMBER_HPP
#define WARBLER_SYNTAX_TYPE_MEMBER_HPP

// local headers
#include <warbler/syntax/identifier.hpp>
#include <warbler/syntax/type.hpp>

namespace warbler::syntax
{
	class Member
	{
	private:

		Identifier _name;
		Type _type;
		bool _is_public;

	public:

		Member(Identifier&& id, Type&& type, bool is_public);

		static Result<Member> parse(lexicon::Token& token);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;

		const Identifier& name() const { return _name; }
		const Type& type() const { return _type; }
	};
}

#endif
