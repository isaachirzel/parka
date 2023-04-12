#ifndef PARKA_SYNTAX_OPERATOR_OPERATOR_SYNTAX_HPP
#define PARKA_SYNTAX_OPERATOR_OPERATOR_SYNTAX_HPP

#include "parka/enum/OperatorType.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	class OperatorId
	{
		OperatorType _type;
		u32 _index;

	public:

		OperatorId(OperatorType type, u32 index) :
		_type(type),
		_index(index)
		{}
		OperatorId(OperatorId&&) = default;
		OperatorId(const OperatorId&) = default;
		~OperatorId() = default;

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }
	};
}

#endif
