#ifndef PARKA_IR_TYPE_IR_HPP
#define PARKA_IR_TYPE_IR_HPP

#include "parka/util/String.hpp"

namespace parka::ir
{
	struct TypeIr
	{
		virtual ~TypeIr() {}
		
		virtual const String& symbol() const = 0;

		friend std::ostream& operator<<(std::ostream& out, const TypeIr& typeBase);
	};
}

#endif
