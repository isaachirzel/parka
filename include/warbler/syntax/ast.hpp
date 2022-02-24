#ifndef WARBLER_SYNTAX_AST_HPP
#define WARBLER_SYNTAX_AST_HPP

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
	
		static Result<Ast> parse(const Array<lexicon::Token>& tokens);

		void print_tree(u32 depth = 0) const;
		bool validate();
	};
}

#endif
