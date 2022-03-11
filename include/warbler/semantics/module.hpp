#ifndef WARBLER_SEMANTICS_MODULE_HPP
#define WARBLER_SEMANTICS_MODULE_HPP

#include <warbler/util/string.hpp>

namespace warbler::semantics
{
	class Module
	{
		String _name;
		Table<Symbol> _symbols;

		Module(String&& name, Table<Symbol>&& symbols);

	public:

		static Result<Module> validate(const syntax::Module& syntax);
	};
}

#endif