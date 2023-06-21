#ifndef PARKA_SYMBOL_DECLARABLE_HPP
#define PARKA_SYMBOL_DECLARABLE_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/enum/DeclarableType.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	struct Declarable : public Resolvable
	{
		const DeclarableType declarableType;

		Declarable(DeclarableType declarableType, ResolvableType resolvableType) :
		Resolvable(resolvableType),
		declarableType(declarableType)
		{}
		virtual ~Declarable() {}

		virtual const ast::Identifier& identifier() const = 0;
	};
}

#endif
