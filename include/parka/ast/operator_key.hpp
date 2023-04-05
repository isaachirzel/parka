#ifndef PARKA_OPERATOR_OPERATOR_KEY_HPP
#define PARKA_OPERATOR_OPERATOR_KEY_HPP

#include "parka/ast/operator_id.hpp"
#include "parka/type/type_key.hpp"

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
	~OperatorKey() = default;

	friend bool operator==(const OperatorKey& left, const OperatorKey& right);

	const auto& operatorType() const { return _operatorType; }
	const auto& leftKey() const { return _leftKey; }
	const auto& rightKey() const { return _rightKey; }
};

template <>
u64 hash64(const OperatorKey& key);

namespace std
{
	template <>
	struct hash<OperatorKey>
	{
		usize operator()(const OperatorKey& key) const { return hash64(key); }
	};
}

#endif
