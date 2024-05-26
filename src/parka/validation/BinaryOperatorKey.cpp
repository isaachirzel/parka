// #include "parka/validation/BinaryOperatorKey.hpp"
// #include "parka/ir/TypeIr.hpp"
// #include "parka/util/Hash.hpp"

// namespace parka::validation
// {
// 	BinaryOperatorKey::BinaryOperatorKey():
// 		_left(&ir::VoidPrimitiveIr::voidPrimitive),
// 		_right(&ir::VoidPrimitiveIr::voidPrimitive),
// 		_binaryExpressionType(BinaryExpressionType::Add)
// 	{}

// 	BinaryOperatorKey::BinaryOperatorKey(const ir::TypeIr& left, const ir::TypeIr& right, BinaryExpressionType binaryExpressionType):
// 		_left(&left),
// 		_right(&right),
// 		_binaryExpressionType(binaryExpressionType)
// 	{}

// 	bool BinaryOperatorKey::operator==(const BinaryOperatorKey& other) const
// 	{
// 		return _left == other._left && _right == other._right && _binaryExpressionType == other._binaryExpressionType;
// 	}
// }

// std::size_t std::hash<parka::validation::BinaryOperatorKey>::operator()(const parka::validation::BinaryOperatorKey& key) const
// {
// 	return parka::hashNumber((size_t)key._left) ^ parka::hashNumber((size_t)key._right) ^ parka::hashNumber((size_t)key._binaryExpressionType);
// }
