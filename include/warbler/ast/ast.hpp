#ifndef WARBLER_PARSER_HPP
#define WARBLER_PARSER_HPP

// local headers
#include <warbler/ast/program.hpp>

namespace warbler
{
	class Ast
	{
	private:

		Program _program;

	public:

		Ast(Program&& program);

		static Result<Ast> parse(const std::vector<Token>& tokens);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
