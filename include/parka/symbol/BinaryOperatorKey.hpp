#ifndef PARKA_SYMBOL_BINARY_OPERATOR_KEY_HPP
#define PARKA_SYMBOL_BINARY_OPERATOR_KEY_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka
{
	class BinaryOperatorKey
	{
		ir::TypeIr _left;
		ir::TypeIr _right;
		BinaryExpressionType _binaryExpressionType;

	public:

		BinaryOperatorKey();
		BinaryOperatorKey(const ir::TypeIr& left, const ir::TypeIr& right, BinaryExpressionType binaryExpressionType);
		BinaryOperatorKey(BinaryOperatorKey&&) = default;
		BinaryOperatorKey(const BinaryOperatorKey&) = default;
		BinaryOperatorKey& operator=(BinaryOperatorKey&&) = default;
		BinaryOperatorKey& operator=(const BinaryOperatorKey&) = default;

		bool operator==(const BinaryOperatorKey& other) const;

		friend struct std::hash<BinaryOperatorKey>;
	};
}

template<>
struct std::hash<parka::BinaryOperatorKey>
{
	std::size_t operator()(const parka::BinaryOperatorKey& key) const;
};

#endif
