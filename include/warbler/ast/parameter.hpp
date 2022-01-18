#ifndef WARBLER_AST_PARAMETER_HPP
#define WARBLER_AST_PARAMETER_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/ast/typename.hpp>
#include <warbler/ast/identifier.hpp>
#include <warbler/util/result.hpp>

namespace warbler
{
	class Parameter
	{
	private:

		Identifier _name;
		Typename _type;

	public:

		Parameter(Identifier&& name, Typename&& type);

		static Result<Parameter> parse(TokenIterator& iter);
		static Result<std::vector<Parameter>> parse_list(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
