#ifndef PARKA_SYMBOL_RESOLVABLE_HPP
#define PARKA_SYMBOL_RESOLVABLE_HPP

#include "parka/enum/ResolvableType.hpp"
#include "parka/util/String.hpp"
#include "parka/ir/LValue.hpp"

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

		virtual const String& name() const = 0;
		virtual ir::LValue *resolve() = 0;

		friend std::ostream& operator<<(std::ostream& out, const Resolvable& resolvabe);
	};
}

#endif
