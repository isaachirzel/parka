#ifndef WARBLER_PROGRAM_HPP
#define WARBLER_PROGRAM_HPP

// local headers
#include <warbler/ast/function.hpp>
#include <warbler/util/table.hpp>
#include <warbler/semantics/symbol.hpp>

namespace warbler
{
	class Program
	{
	private:
		
		Table<u32> _types;
		Table<Symbol> _symbols;
		std::vector<Function> _functions;

	public:

		Program(std::vector<Function>&& functions);

		static Result<Program> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
		bool validate();
	};
}

#endif
