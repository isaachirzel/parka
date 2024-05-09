#ifndef PARKA_IR_SYMBOLED_HPP
#define PARKA_IR_SYMBOLED_HPP

#include "parka/util/String.hpp"

namespace parka::ir
{
	struct SymboledIr
	{
		virtual ~SymboledIr() {}
		virtual const String& symbol() const =  0;
	};
}

#endif
