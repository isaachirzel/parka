#ifndef PARKA_EVALUATION_VALUE_HPP
#define PARKA_EVALUATION_VALUE_HPP

#include "parka/ir/Type.hpp"

namespace parka::evaluation
{
	struct Value
	{
		virtual ~Value() {}
		virtual Value& add(const Value& other) const = 0;
		virtual const ir::Type& type() const = 0;
	};
}

#endif
