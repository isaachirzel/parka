#include "parka/ir/IntrinsicOperator.hpp"
#include "parka/enum/OperatorType.hpp"

namespace parka::ir
{
	template <typename Left, typename Right>
	IntrinsicOperatorIr op(OperatorType type)
	{
		const auto& l = ir::Type::of<Left>();
		const auto& r = ir::Type::of<Right>();
		const auto& ret = sizeof(Left) >= sizeof(Right) ? l : r;

		return IntrinsicOperatorIr(type, l, r, ret);
	}

	template <typename Left, typename Right>
	IntrinsicOperatorIr add()
	{
		return op<Left, Right>(OperatorType::Add);
	}

	template <typename Left, typename Right>
	IntrinsicOperatorIr subtract()
	{
		return op<Left, Right>(OperatorType::Subtract);
	}

	template <typename Left, typename Right>
	IntrinsicOperatorIr multiply()
	{
		return op<Left, Right>(OperatorType::Multiply);
	}

	template <typename Left, typename Right>
	IntrinsicOperatorIr divide()
	{
		return op<Left, Right>(OperatorType::Divide);
	}

	IntrinsicOperatorIr add(const Type& left, const Type& right, const Type& ret)
	{
		return IntrinsicOperatorIr(OperatorType::Add, left, right, ret);
	}

	IntrinsicOperatorIr subtract(const Type& left, const Type& right, const Type& ret)
	{
		return IntrinsicOperatorIr(OperatorType::Subtract, left, right, ret);
	}

	IntrinsicOperatorIr multiply(const Type& left, const Type& right, const Type& ret)
	{
		return IntrinsicOperatorIr(OperatorType::Multiply, left, right, ret);
	}

	IntrinsicOperatorIr divide(const Type& left, const Type& right, const Type& ret)
	{
		return IntrinsicOperatorIr(OperatorType::Divide, left, right, ret);
	}

	IntrinsicOperatorIr addIntToInt()
	{
		return IntrinsicOperatorIr(OperatorType::Add, Type::integerLiteralType, Type::integerLiteralType, Type::integerLiteralType);
	}

	IntrinsicOperatorIr subtractIntFromInt()
	{
		return IntrinsicOperatorIr(OperatorType::Subtract, Type::integerLiteralType, Type::integerLiteralType, Type::integerLiteralType);
	}

	IntrinsicOperatorIr multiplyIntAndInt()
	{
		return IntrinsicOperatorIr(OperatorType::Multiply, Type::integerLiteralType, Type::integerLiteralType, Type::integerLiteralType);
	}

	IntrinsicOperatorIr divideIntByInt()
	{
		return IntrinsicOperatorIr(OperatorType::Divide, Type::integerLiteralType, Type::integerLiteralType, Type::integerLiteralType);
	}

	IntrinsicOperatorIr IntrinsicOperatorIr::entries[] =
	{
		addIntToInt(),
		subtractIntFromInt(),
		multiplyIntAndInt(),
		divideIntByInt(),

		add<u8, u8>(),
		subtract<u8, u8>(),
		multiply<u8, u8>(),
		divide<u8, u8>(),

		add<u16, u16>(),
		subtract<u16, u16>(),
		multiply<u16, u16>(),
		divide<u16, u16>(),

		add<u32, u32>(),
		subtract<u32, u32>(),
		multiply<u32, u32>(),
		divide<u32, u32>(),

		add<u64, u64>(),
		subtract<u64, u64>(),
		multiply<u64, u64>(),
		divide<u64, u64>(),

		add<f32, f32>(),
		subtract<f32, f32>(),
		multiply<f32, f32>(),
		divide<f32, f32>(),

		add<f64, f64>(),
		subtract<f64, f64>(),
		multiply<f64, f64>(),
		divide<f64, f64>(),
	};
	const usize IntrinsicOperatorIr::entryCount = sizeof(entries) / sizeof(*entries);

	IntrinsicOperatorIr::IntrinsicOperatorIr(OperatorType operatorType, const Type& type, const Type& returnType):
		OperatorIr(true),
		_lhs(type),
		_rhs(nullptr),
		_returnType(returnType),
		_operatorType(operatorType)
	{}

	IntrinsicOperatorIr::IntrinsicOperatorIr(OperatorType operatorType, const Type& lhs, const Type& rhs, const Type& returnType):
		OperatorIr(true),
		_lhs(lhs),
		_rhs(&rhs),
		_returnType(returnType),
		_operatorType(operatorType)
	{}
}
