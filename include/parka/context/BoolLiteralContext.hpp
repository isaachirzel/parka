#ifndef PARKA_CONTEXT_BOOL_LITERAL_CONTEXT_HPP
#define PARKA_CONTEXT_BOOL_LITERAL_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"

namespace parka
{
	class BoolLiteralContext : public ExpressionContext
	{
		bool _value;

	public:

		BoolLiteralContext(bool value);
		BoolLiteralContext(BoolLiteralContext&&) = default;
		BoolLiteralContext(const BoolLiteralContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::BoolLiteral; }
		const auto& value() const { return _value; }
	};
}

#endif
