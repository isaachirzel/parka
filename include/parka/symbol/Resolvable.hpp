#ifndef PARKA_SYMBOL_RESOLVABLE_HPP
#define PARKA_SYMBOL_RESOLVABLE_HPP

#include "parka/enum/ResolvableType.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/String.hpp"
#include "parka/ir/LValueIr.hpp"

namespace parka
{
	struct Resolvable
	{
		const ResolvableType resolvableType;

	public:

		Resolvable(ResolvableType resolvableType):
			resolvableType(resolvableType)
		{}
		virtual ~Resolvable() {}

		virtual SymbolTable* symbolTable() = 0;
		virtual const String& name() const = 0;
		virtual ir::LValueIr *resolve() = 0;

		friend std::ostream& operator<<(std::ostream& out, const Resolvable& resolvabe);
	};
}

#endif
