#include "parka/ir/IntrinsicOperator.hpp"
#include "parka/enum/OperatorType.hpp"
#include "parka/util/Float.hpp"

namespace parka::ir
{
	template <typename T>
	IntrinsicOperatorIr op(OperatorType operatorType)
	{
		const auto& type = ir::Type::of<T>();

		return IntrinsicOperatorIr(operatorType, type, type, type);
	}

	template <typename T>
	IntrinsicOperatorIr add()
	{
		return op<T>(OperatorType::Add);
	}

	template <typename T>
	IntrinsicOperatorIr subtract()
	{
		return op<T>(OperatorType::Subtract);
	}

	template <typename T>
	IntrinsicOperatorIr multiply()
	{
		return op<T>(OperatorType::Multiply);
	}

	template <typename T>
	IntrinsicOperatorIr divide()
	{
		return op<T>(OperatorType::Divide);
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
		add<Integer>(),
		subtract<Integer>(),
		multiply<Integer>(),
		divide<Integer>(),

		add<Float>(),
		subtract<Float>(),
		multiply<Float>(),
		divide<Float>(),

		add<u8>(),
		subtract<u8>(),
		multiply<u8>(),
		divide<u8>(),

		add<u16>(),
		subtract<u16>(),
		multiply<u16>(),
		divide<u16>(),

		add<u32>(),
		subtract<u32>(),
		multiply<u32>(),
		divide<u32>(),

		add<u64>(),
		subtract<u64>(),
		multiply<u64>(),
		divide<u64>(),

		add<i8>(),
		subtract<i8>(),
		multiply<i8>(),
		divide<i8>(),

		add<i16>(),
		subtract<i16>(),
		multiply<i16>(),
		divide<i16>(),

		add<i32>(),
		subtract<i32>(),
		multiply<i32>(),
		divide<i32>(),

		add<i64>(),
		subtract<i64>(),
		multiply<i64>(),
		divide<i64>(),

		add<f32>(),
		subtract<f32>(),
		multiply<f32>(),
		divide<f32>(),

		add<f64>(),
		subtract<f64>(),
		multiply<f64>(),
		divide<f64>()
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
