#ifndef PARKA_OPERATOR_OPERATOR_KEY_HPP
#define PARKA_OPERATOR_OPERATOR_KEY_HPP

#include "parka/repository/OperatorId.hpp"
#include "parka/symbol/TypeKey.hpp"

#include <functional>

namespace parka
{
	class OperatorKey
	{
		OperatorType _operatorType;
		TypeKey _leftKey;
		TypeKey _rightKey;

	public:

		OperatorKey(OperatorType operatorType, const TypeKey& leftKey, const TypeKey& rightKey) :
		_operatorType(operatorType),
		_leftKey(leftKey),
		_rightKey(rightKey)
		{}
		OperatorKey(OperatorKey&&) = default;
		OperatorKey(const OperatorKey&) = default;

		friend bool operator==(const OperatorKey& left, const OperatorKey& right);

		const auto& operatorType() const { return _operatorType; }
		const auto& leftKey() const { return _leftKey; }
		const auto& rightKey() const { return _rightKey; }
	};
}

namespace std
{
	template <>
	struct hash<parka::OperatorKey>
	{
		parka::usize operator()(const parka::OperatorKey& key) const;
	};
}

#endif
