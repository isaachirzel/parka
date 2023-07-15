#ifndef PARKA_IR_OPERATOR_HPP
#define PARKA_IR_OPERATOR_HPP

#include "parka/enum/OperatorType.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/ir/Parameter.hpp"
#include "parka/ir/Type.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class OverloadedOperatorIr
	{
		Array<ParameterIr*> _parameters;
		Type _returnType;
		OperatorType _operatorType;
		ExpressionIr *_body;

	public:

		OverloadedOperatorIr(OperatorType operatorType, Array<ParameterIr*>&& parameters, Type&& returnType):
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType)),
		_operatorType(operatorType)
		{}
		OverloadedOperatorIr(OverloadedOperatorIr&&) = default;
		OverloadedOperatorIr(const OverloadedOperatorIr&) = delete;

		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }
		const auto& operatorType() const { return _operatorType; }
		const auto *body() const { return _body; }
		bool isIntrinsic() const { return !_body; }
	};
}

#endif
