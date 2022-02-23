#ifndef WARBLER_SYNTAX_MODULE_HPP
#define WARBLER_SYNTAX_MODULE_HPP

// local headers
#include <warbler/syntax//function.hpp>
#include <warbler/util/table.hpp>
#include <warbler/syntax//type/type_definition.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::syntax
{
	class Module
	{
	private:
		
		semantics::ModuleContext _context;

		Array<Function> _functions;
		Array<Ptr<TypeDefinition>> _types;

		Module(Array<Function>&& functions, Array<Ptr<TypeDefinition>>&& types);

	public:

		static Result<Module> parse(TokenIterator& iter);

		bool validate(const String& module_name);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
