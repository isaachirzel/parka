#include "parka/ir/FloatLiteralIr.hpp"
namespace parka::ir
{
	FloatLiteralIr::FloatLiteralIr(f64 value):
		ExpressionIr(ExpressionType::FloatLiteral),
		_value(value)
	{}
}
