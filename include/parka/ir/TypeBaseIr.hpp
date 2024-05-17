#ifndef PARKA_IR_TYPENAME_HPP
#define PARKA_IR_TYPENAME_HPP

#include "parka/util/String.hpp"

namespace parka::ir
{
	struct TypeBaseIr
	{
		virtual ~TypeBaseIr() {}
		
		virtual const String& symbol() const = 0;

		friend std::ostream& operator<<(std::ostream& out, const TypeBaseIr& typeBase);
	};
}

#endif
