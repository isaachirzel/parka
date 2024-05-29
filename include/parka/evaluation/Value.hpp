#ifndef PARKA_EVALUATION_VALUE_HPP
#define PARKA_EVALUATION_VALUE_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Common.hpp"

namespace parka::evaluation
{
	class Value
	{
		const ir::TypeIr& _type;
		u64 _value;
		const ir::EntityIr* _nodePtr;

	private:

		void setValue(const byte* data, usize size);

	public:

		Value(const ir::TypeIr& type);
		Value(Value&&);
		Value(const Value&) = delete;

		void setNode(const ir::EntityIr& nodePtr);
		const ir::EntityIr* nodePtr() { return _nodePtr; }

		void setValue(const Value& other);

		template <typename T>
		void setValue(const T& value)
		{
			return setValue((const byte*)&value, sizeof(T));
		}

		template <typename T>
		const T& getValue() const
		{
			return *(const T*)&_value;
		}

		template <typename T>
		T& getValue()
		{
			return *(T*)&_value;
		}

		const ir::TypeIr& type() const { return _type; }

		friend std::ostream& operator<<(std::ostream& out, const Value& value);
	};
	
}

#endif
