#ifndef PARKA_IR_TYPED_HPP
#define PARKA_IR_TYPED_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	struct TypedIr
	{
		virtual ~TypedIr() {}
		virtual const TypeIr& type() const =  0;
	};
}

#endif
