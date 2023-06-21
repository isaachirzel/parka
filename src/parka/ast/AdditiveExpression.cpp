#include "parka/ast/AdditiveExpression.hpp"
#include "parka/ir/AdditiveExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/MultiplicativeExpression.hpp"

namespace parka::ast
{	
	static Optional<AdditiveType> getAdditiveType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Plus:
				return AdditiveType::Add;

			case TokenType::Minus:
				return AdditiveType::Subtract;

			default:
				break;
		}

		return {};
	}

	ExpressionAst *AdditiveExpressionAst::parse(Token& token)
	{
		auto *lhs = MultiplicativeExpressionAst::parse(token);

		if (!lhs)
			return {};
		
		auto type = getAdditiveType(token);

		while (type)
		{
			token.increment();

			auto rhs = MultiplicativeExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new AdditiveExpressionAst(*lhs, *rhs, *type);
			type = getAdditiveType(token);
		}

		return lhs;
	}

	// ir::ExpressionIr *AdditiveExpressionAst::validate(SymbolTable& symbolTable)
	// {
	// 	auto *lhs = _lhs.validate(symbolTable);
	// 	auto *rhs = _rhs.validate(symbolTable);

	// 	// TODO: Operators

	// 	if (!lhs || !rhs)
	// 		return nullptr;

	// 	const auto& lhsType = lhs->valueType();
	// 	const auto& rhsType = rhs->valueType();

	// 	if (!rhsType.canConvertTo(lhsType))
	// 	{
	// 		log::error(_snippet, "$ cannot be added to $.", rhsType, lhsType);
	// 		return nullptr;
	// 	}

	// 	auto *context = new ir::AdditiveExpressionIr(*lhs, *rhs, _additiveType, ir::ValueType(lhsType));

	// 	return context;
	// }
}
