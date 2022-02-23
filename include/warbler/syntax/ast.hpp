#ifndef WARBLER_PARSER_HPP
#define WARBLER_PARSER_HPP

// local headers
#include <warbler/syntax//module.hpp>

namespace warbler::syntax
{
	class Ast
	{
	private:

		Module _module;

		Ast(Module&& program);

	public:
	
		static Result<Ast> parse(const std::vector<Token>& tokens);

		void print_tree(u32 depth = 0) const;
		bool validate();
	};
}

#endif
