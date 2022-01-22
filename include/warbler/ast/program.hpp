#ifndef WARBLER_PROGRAM_HPP
#define WARBLER_PROGRAM_HPP

// local headers
#include <warbler/ast/function.hpp>
#include <warbler/util/table.hpp>
#include <warbler/ast/type/type_definition.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Program
	{
	private:
		
		semantics::Context _context;

		Array<Function> _functions;
		Array<TypeDefinition> _types;

		Program(Array<Function>&& functions, Array<TypeDefinition>&& types);

	public:

		static Result<Program> parse(TokenIterator& iter);

		bool validate();
		void print_tree(u32 depth = 0) const;
	};
}

#endif
