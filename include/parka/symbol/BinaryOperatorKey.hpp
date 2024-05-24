#ifndef PARKA_SYMBOL_BINARY_OPERATOR_KEY_HPP
#define PARKA_SYMBOL_BINARY_OPERATOR_KEY_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka
{
	class BinaryOperatorKey
	{
		ir::TypeIr _to;
		ir::TypeIr _from;
		BinaryExpressionType _binaryExpressionType;

	public:

		BinaryOperatorKey();
		BinaryOperatorKey(const ir::TypeIr& to, const ir::TypeIr& from, BinaryExpressionType binaryExpressionType);
		BinaryOperatorKey(BinaryOperatorKey&&) = default;
		BinaryOperatorKey(const BinaryOperatorKey&) = delete;
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
