#ifndef PARKA_IR_TYPE_IR_HPP
#define PARKA_IR_TYPE_IR_HPP

#include "parka/enum/TypeCategory.hpp"

namespace parka::ir
{
	struct TypeIr
	{
		const TypeCategory typeCategory;

		TypeIr(TypeCategory typeCategory):
			typeCategory(typeCategory)
		{}
		virtual ~TypeIr() {}

		virtual std::ostream& printType(std::ostream&) const = 0;

		virtual bool operator==(const TypeIr& other) const { return this == &other; }
		virtual bool operator!=(const TypeIr& other) const { return this != &other; }

		friend std::ostream& operator<<(std::ostream& out, const TypeIr& type)
		{
			return type.printType(out);
		}
	};
}

#endif
