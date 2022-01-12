#ifndef WARBLER_PROGRAM_HPP
#define WARBLER_PROGRAM_HPP

// local headers
#include <warbler/ast/function.hpp>
namespace warbler
{
	class Program
	{
	private:

		std::vector<Function> _functions;

	public:

		Program(std::vector<Function>&& functions);

		static Result<Program> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}
#endif
