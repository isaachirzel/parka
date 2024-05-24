#include "parka/symbol/BinaryOperatorKey.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Hash.hpp"

namespace parka
{
	BinaryOperatorKey::BinaryOperatorKey():
		_left(ir::TypeIr::voidType),
		_right(ir::TypeIr::voidType),
		_binaryExpressionType(BinaryExpressionType::Add)
	{}

	BinaryOperatorKey::BinaryOperatorKey(const ir::TypeIr& left, const ir::TypeIr& right, BinaryExpressionType binaryExpressionType):
		_left(left),
		_right(right),
		_binaryExpressionType(binaryExpressionType)
	{}

	bool BinaryOperatorKey::operator==(const BinaryOperatorKey& other) const
	{
		return _left == other._left && _right == other._right && _binaryExpressionType == other._binaryExpressionType;
	}
}

std::size_t std::hash<parka::BinaryOperatorKey>::operator()(const parka::BinaryOperatorKey& key) const
{
	// TODO: Idk lol figure out how to hash the enum
	auto typeHasher = std::hash<parka::ir::TypeIr>();

	return typeHasher(key._left) ^ typeHasher(key._right) ^ parka::hashNumber((size_t)key._binaryExpressionType);
}
