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
		byte _value[8];
		const ir::LValueIr* _nodePtr;

	private:

		void setValue(const byte* data, usize size);

	public:

		Value(const ir::Type& type);
		Value(Value&&);
		Value(const Value&) = delete;

		void setNode(const ir::LValueIr& nodePtr);
		const ir::LValueIr* nodePtr() { return _nodePtr; }

		void setValue(const Value& other);
		template <typename T>
		void setValue(const T& value)
		{
			return setValue((const byte*)&value, sizeof(T));
		}

		template <typename T>
		T getValue()
		{
			return *(T*)_value;
		}
		
		const byte* value() const { return _value; }

		const ir::Type& type() const { return _type; }

		friend std::ostream& operator<<(std::ostream& out, const Value& value);
	};
	
}

#endif
