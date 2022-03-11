#ifndef WARBLER_SYNTAX_MODULE_HPP
#define WARBLER_SYNTAX_MODULE_HPP

// local headers
#include <warbler/syntax/function/function.hpp>
#include <warbler/util/table.hpp>
#include <warbler/syntax/type/type_definition.hpp>

namespace warbler::syntax
{
	class Module
	{
	private:

		Array<Function> _functions;
		Array<Ptr<TypeDefinition>> _types;

	public:

		Module(Array<Function>&& functions, Array<Ptr<TypeDefinition>>&& types);

		static Result<Module> parse(lexicon::Token& token);
	};
}

#endif
