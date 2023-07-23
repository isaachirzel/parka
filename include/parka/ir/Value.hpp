#ifndef PARKA_IR_VALUE_HPP
#define PARKA_IR_VALUE_HPP

#include "parka/ir/Type.hpp"

namespace parka::ir
{
	struct Value
	{
		virtual ~Value() {}
		virtual const Type& type() const = 0;
	};
}

#endif
