// #include "parka/ast/OperatorKeyAst.hpp"
// #include "parka/util/Common.hpp"
// #include "parka/util/Print.hpp"
// #include <functional>

// namespace parka::ast
// {
// 	bool operator==(const OperatorKey& left, const OperatorKey& right)
// 	{
// 		return left._operatorType == right._operatorType
// 			&& left._leftKey == right._leftKey
// 			&& left._rightKey == right._rightKey;
// 	}
// }

// namespace std
// {
// 	using namespace parka;

// 	usize hash<OperatorKey>::operator()(const OperatorKey& key) const
// 	{
// 		auto value = std::hash<u64>{}((u64)key.operatorType());

// 		value ^= hash<TypeKey>()(key.leftKey());
// 		value ^= hash<TypeKey>()(key.rightKey());

// 		return value;
// 	}
// }
