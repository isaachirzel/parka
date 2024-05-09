#ifndef PARKA_EVALUATION_VALUE_HPP
#define PARKA_EVALUATION_VALUE_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Common.hpp"

namespace parka::evaluation
{
	class Value
	{
		ir::Type _type;
		alignas(u64) byte _value[sizeof(u64)];
		const ir::LValueIr* _nodePtr;

	public:

		Value(const ir::Type& type);
		Value(Value&&);
		Value(const Value&) = delete;

		// Value& operator=(Value&& other);
		Value& operator=(const Value& other);

		void setNode(const ir::LValueIr& nodePtr);
		const ir::LValueIr* nodePtr() { return _nodePtr; }


		void set(const byte* data, usize size);
		// void set(const Value& other);
		const byte* value() const { return _value; }

		const ir::Type& type() const { return _type; }

		friend std::ostream& operator<<(std::ostream& out, const Value& value);
	};
	
}

#endif
