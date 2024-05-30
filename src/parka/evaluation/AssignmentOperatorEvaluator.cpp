#include "parka/evaluation/AssignmentOperatorEvaluator.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/PrimitiveType.hpp"
#include "parka/enum/TypeCategory.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

using namespace parka::ir;

namespace parka::evaluation
{
	template <typename Left, typename Right, void(*operation)(AssignmentType, Left&, const Right&)>
	void evaluateIntrinsicAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		auto& l = left.getValue<Left>();
		auto& r = right.getValue<Right>();

		operation(ir.assignmentType(), l, r);
	}

	template <typename Left, typename Right>
	void _integerAssignment(AssignmentType assignmentType, Left& l, const Right& r)
	{
		const Left& cr = (const Left&)r;

		switch (assignmentType)
		{
			case AssignmentType::Assign:
				l = cr;
				return;

			case AssignmentType::AddAssign:
				l += cr;
				return;

			case AssignmentType::SubtractAssign:
				l -= cr;
				return;

			case AssignmentType::MultiplyAssign:
				l *= cr;
				return;

			case AssignmentType::DivideAssign:
				l /= cr;
				return;

			case AssignmentType::ModulusAssign:
				l %= cr;
				return;

			case AssignmentType::LeftShiftAssign:
				l <<= cr;
				return;

			case AssignmentType::RightShiftAssign:
				l >>= cr;
				return;

			case AssignmentType::BitwiseOrAssign:
				l |= cr;
				return;

			case AssignmentType::BitwiseXorAssign:
				l ^= cr;
				return;

			case AssignmentType::BitwiseAndAssign:
				l &= cr;
				return;

			default:
				break;
		}

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", l, assignmentType, r);
	}
	
	template <typename Left, typename Right>
	void evaluateIntrinsicIntegerAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		return evaluateIntrinsicAssignmentOperator<Left, Right, _integerAssignment>(ir, left, right);
	}

	template <typename Left>
	void evaluateIntrinsicIntegerAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		const PrimitiveIr& primitive = dynamic_cast<const PrimitiveIr&>(ir.right());

		switch (primitive.primitiveType())
		{
			case PrimitiveType::Integer:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, Integer>(ir, left, right);

			case PrimitiveType::I8:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, i8>(ir, left, right);

			case PrimitiveType::I16:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, i16>(ir, left, right);

			case PrimitiveType::I32:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, i32>(ir, left, right);

			case PrimitiveType::I64:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, i64>(ir, left, right);

			case PrimitiveType::U8:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, u8>(ir, left, right);

			case PrimitiveType::U16:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, u16>(ir, left, right);

			case PrimitiveType::U32:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, u32>(ir, left, right);

			case PrimitiveType::U64:
				return evaluateIntrinsicIntegerAssignmentOperator<Left, u64>(ir, left, right);

			default:
				break;
		}

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", left.type(), ir.assignmentType(), right.type());
	}

	template <typename Left, typename Right>
	void _floatAssignment(AssignmentType assignmentType, Left& l, const Right& r)
	{
		const Left& cr = (const Left&)r;

		switch (assignmentType)
		{
			case AssignmentType::Assign:
				l = cr;
				return;

			case AssignmentType::AddAssign:
				l += cr;
				return;

			case AssignmentType::SubtractAssign:
				l -= cr;
				return;

			case AssignmentType::MultiplyAssign:
				l *= cr;
				return;

			case AssignmentType::DivideAssign:
				l /= cr;
				return;

			default:
				break;
		}

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", l, assignmentType, r);
	}

	template <typename Left, typename Right>
	void evaluateIntrinsicFloatAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		return evaluateIntrinsicAssignmentOperator<Left, Right, _floatAssignment>(ir, left, right);
	}

	template <typename Left>
	void evaluateIntrinsicFloatAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		const PrimitiveIr& primitive = dynamic_cast<const PrimitiveIr&>(ir.right());

		switch (primitive.primitiveType())
		{
			case PrimitiveType::Float:
				return evaluateIntrinsicFloatAssignmentOperator<Left, Float>(ir, left, right);

			case PrimitiveType::F32:
				return evaluateIntrinsicFloatAssignmentOperator<Left, f32>(ir, left, right);

			case PrimitiveType::F64:
				return evaluateIntrinsicFloatAssignmentOperator<Left, f64>(ir, left, right);

			default:
				break;
		}

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", left.type(), ir.assignmentType(), right.type());
	}

	template <typename Left, typename Right>
	void _boolAssignment(AssignmentType assignmentType, Left& l, const Right r)
	{
		if (assignmentType == AssignmentType::Assign)
		{
			l = (const Left&)r;
			return;
		}

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", l, assignmentType, r);
	}

	template <typename Left, typename Right>
	void evaluateIntrinsicBoolAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		return evaluateIntrinsicAssignmentOperator<Left, Right, _boolAssignment>(ir, left, right);
	}

	template <typename Left>
	void evaluateIntrinsicBoolAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		const PrimitiveIr& primitive = dynamic_cast<const PrimitiveIr&>(ir.right());

		if (primitive.primitiveType() == PrimitiveType::Bool)
			return evaluateIntrinsicBoolAssignmentOperator<Left, bool>(ir, left, right);

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", left.type(), ir.assignmentType(), right.type());
	}

	template <typename Left, typename Right>
	void _charAssignment(AssignmentType assignmentType, Left& l, const Right r)
	{
		if (assignmentType == AssignmentType::Assign)
		{
			l = (const Left&)r;
			return;
		}

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", l, assignmentType, r);
	}

	template <typename Left, typename Right>
	void evaluateIntrinsicCharAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		return evaluateIntrinsicAssignmentOperator<Left, Right, _charAssignment>(ir, left, right);
	}

	template <typename Left>
	void evaluateIntrinsicCharAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		const PrimitiveIr& primitive = dynamic_cast<const PrimitiveIr&>(ir.right());

		if (primitive.primitiveType() == PrimitiveType::Char)
			return evaluateIntrinsicCharAssignmentOperator<Left, char>(ir, left, right);

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", left.type(), ir.assignmentType(), right.type());
	}

	void evaluateIntrinsicAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, const Value& right)
	{
		const PrimitiveIr& primitive = dynamic_cast<const PrimitiveIr&>(ir.left());

		switch (primitive.primitiveType())
		{
			case PrimitiveType::I8:
				return evaluateIntrinsicIntegerAssignmentOperator<i8>(ir, left, right);

			case PrimitiveType::I16:
				return evaluateIntrinsicIntegerAssignmentOperator<i16>(ir, left, right);

			case PrimitiveType::I32:
				return evaluateIntrinsicIntegerAssignmentOperator<i32>(ir, left, right);

			case PrimitiveType::I64:
				return evaluateIntrinsicIntegerAssignmentOperator<i64>(ir, left, right);

			case PrimitiveType::U8:
				return evaluateIntrinsicIntegerAssignmentOperator<u8>(ir, left, right);

			case PrimitiveType::U16:
				return evaluateIntrinsicIntegerAssignmentOperator<u16>(ir, left, right);

			case PrimitiveType::U32:
				return evaluateIntrinsicIntegerAssignmentOperator<u32>(ir, left, right);

			case PrimitiveType::U64:
				return evaluateIntrinsicIntegerAssignmentOperator<u64>(ir, left, right);

			case PrimitiveType::F32:
				return evaluateIntrinsicFloatAssignmentOperator<f32>(ir, left, right);

			case PrimitiveType::F64:
				return evaluateIntrinsicFloatAssignmentOperator<f64>(ir, left, right);

			case PrimitiveType::Bool:
				return evaluateIntrinsicBoolAssignmentOperator<bool>(ir, left, right);

			case PrimitiveType::Char:
				return evaluateIntrinsicCharAssignmentOperator<char>(ir, left, right);

			default:
				break;
		}

		log::fatal("Assignment operator `$ $ $` cannot be evaluated.", left.type(), ir.assignmentType(), right.type());
	}

	void evaluateAssignmentOperator(const AssignmentOperatorIr& ir, Value& left, Value& right, LocalState&)
	{
		return evaluateIntrinsicAssignmentOperator(ir, left, right);
	}
}
