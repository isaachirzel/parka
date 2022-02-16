#ifndef WARBLER_AST_MODULE_HPP
#define WARBLER_AST_MODULE_HPP

// local headers
#include <warbler/ast/function.hpp>
#include <warbler/util/table.hpp>
#include <warbler/ast/type/type.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Module
	{
	private:
		
		semantics::ModuleContext _context;

		Array<Function> _functions;
		Array<Type> _types;

		Module(Array<Function>&& functions, Array<Type>&& types);

	public:

		static Result<Module> parse(TokenIterator& iter);

		bool validate(const String& module_name);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
