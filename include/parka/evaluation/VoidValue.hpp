#ifndef PARKA_EVALUATION_VOID_VALUE_HPP
#define PARKA_EVALUATION_VOID_VALUE_HPP

#include "parka/evaluation/Value.hpp"
namespace parka::evaluation
{
	class VoidValue: public Value
	{
	public:

		VoidValue() = default;
		VoidValue(VoidValue&&) = default;
		VoidValue(const VoidValue&) = delete;
		
		Value& add(const Value&) const;
		const ir::Type& type() const { return ir::Type::voidType; }
	};
}

#endif
