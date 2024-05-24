#ifndef PARKA_VALIDATION_BINARY_OPERATOR_KEY_HPP
#define PARKA_VALIDATION_BINARY_OPERATOR_KEY_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::validation
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
struct std::hash<parka::validation::BinaryOperatorKey>
{
	std::size_t operator()(const parka::validation::BinaryOperatorKey& key) const;
};

#endif
