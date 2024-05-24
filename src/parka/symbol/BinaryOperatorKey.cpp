#include "parka/symbol/BinaryOperatorKey.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Hash.hpp"

namespace parka
{
	BinaryOperatorKey::BinaryOperatorKey():
		_to(ir::TypeIr::voidType),
		_from(ir::TypeIr::voidType),
		_binaryExpressionType(BinaryExpressionType::Add)
	{}

	BinaryOperatorKey::BinaryOperatorKey(const ir::TypeIr& to, const ir::TypeIr& from, BinaryExpressionType binaryExpressionType):
		_to(to),
		_from(from),
		_binaryExpressionType(binaryExpressionType)
	{}

	bool BinaryOperatorKey::operator==(const BinaryOperatorKey& other) const
	{
		return _to == other._to && _from == other._from && _binaryExpressionType == other._binaryExpressionType;
	}
}

std::size_t std::hash<parka::BinaryOperatorKey>::operator()(const parka::BinaryOperatorKey& key) const
{
	// TODO: Idk lol figure out how to hash the enum
	auto typeHasher = std::hash<parka::ir::TypeIr>();

	return typeHasher(key._to) ^ typeHasher(key._from) ^ parka::hashNumber((size_t)key._binaryExpressionType);
}
