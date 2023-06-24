#ifndef PARKA_SYMBOL_DECLARABLE_HPP
#define PARKA_SYMBOL_DECLARABLE_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/enum/DeclarableType.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	struct Declarable
	{
		const DeclarableType declarableType;

		Declarable(DeclarableType declarableType):
		declarableType(declarableType)
		{}
		virtual ~Declarable() {}

		virtual const ast::Identifier& identifier() const = 0;
	};
}

#endif
