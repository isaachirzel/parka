#ifndef PARKA_EVALUATION_VALUE_HPP
#define PARKA_EVALUATION_VALUE_HPP

#include "parka/ir/Type.hpp"

namespace parka::evaluation
{
	class Value
	{
		ir::Type _type;
		u64 _value;
		void *_nodePtr;

	public:

		Value(const ir::Type& type, u64 value = 0);
		Value(Value&&) = default;
		Value(const Value&) = delete;

		void nodePtr(void *nodePtr);
		void* nodePtr();

		void value(u64 value) { _value = value; }
		const auto& value() const { return _value; }

		void set(const Value& other);

		const ir::Type& type() const { return _type; }

		friend std::ostream& operator<<(std::ostream& out, const Value& value);
	};
	
}

#endif
