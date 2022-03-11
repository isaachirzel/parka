#ifndef WARBLER_SYNTAX_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_HPP

#include <warbler/syntax/type.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::syntax
{
	class ConditionalExpression;
	class BooleanOrExpression;
	class BooleanAndExpression;
	class BitwiseOrExpression;
	class BitwiseXorExpression;
	class BitwiseAndExpression;
	class EqualityExpression;
	class RelationalExpression;
	class ShiftExpression;
	class AdditiveExpression;
	class MultiplicativeExpression;
	class PrefixExpression;
	class PostfixExpression;
	class PrimaryExpression;
	class Constant;
	class Symbol;

	enum class ExpressionType
	{
		Conditional,
		BooleanOr,
		BooleanAnd,
		BitwiseOr,
		BitwiseXor,
		BitwiseAnd,
		Equality,
		Relational,
		Shift,
		Additive,
		Multiplicative,
		Postfix,
		Prefix,
		Primary,
		Constant,
		Symbol
	};

	class Expression
	{
		union
		{
			ConditionalExpression *_conditional;
			BooleanOrExpression *_boolean_or;
			BooleanAndExpression *_boolean_and;
			BitwiseOrExpression *_bitwise_or;
			BitwiseXorExpression *_bitwise_xor;
			BitwiseAndExpression *_bitwise_and;
			EqualityExpression *_equality;
			RelationalExpression *_relational;
			ShiftExpression *_shift;
			AdditiveExpression *_additive;
			MultiplicativeExpression *_multiplicative;
			PrefixExpression *_prefix;
			PostfixExpression *_postfix;
			PrimaryExpression *_primary;
			Constant *_constant;
			Symbol *_symbol;
		};

		ExpressionType _type;
	
	public:

		Expression(ConditionalExpression&&);
		Expression(BooleanOrExpression&&);
		Expression(BooleanAndExpression&&);
		Expression(BitwiseOrExpression&&);
		Expression(BitwiseXorExpression&&);
		Expression(BitwiseAndExpression&&);
		Expression(EqualityExpression&&);
		Expression(RelationalExpression&&);
		Expression(ShiftExpression&&);
		Expression(AdditiveExpression&&);
		Expression(MultiplicativeExpression&&);
		Expression(PrefixExpression&&);
		Expression(PostfixExpression&&);
		Expression(PrimaryExpression&&);
		Expression(Constant&&);
		Expression(Symbol&&);
		Expression(Expression&&);
		Expression(const Expression&) = delete;
		~Expression();

		static Result<Expression> parse(lexicon::Token& token);

		ExpressionType type() const { return _type; }
		const ConditionalExpression& conditional() const { assert(_type == ExpressionType::Conditional); return *_conditional; }
		const BooleanOrExpression& boolean_or() const { assert(_type == ExpressionType::BooleanOr); return *_boolean_or; }
		const BooleanAndExpression& boolean_and() const { assert(_type == ExpressionType::BooleanAnd); return *_boolean_and; }
		const BitwiseOrExpression& bitwise_or() const { assert(_type == ExpressionType::BitwiseOr); return *_bitwise_or; }
		const BitwiseXorExpression& bitwise_xor() const { assert(_type == ExpressionType::BitwiseXor); return *_bitwise_xor; }
		const BitwiseAndExpression& bitwise_and() const { assert(_type == ExpressionType::BitwiseAnd); return *_bitwise_and; }
		const EqualityExpression& equality() const { assert(_type == ExpressionType::Equality); return *_equality; }
		const RelationalExpression& relational() const { assert(_type == ExpressionType::Relational); return *_relational; }
		const ShiftExpression& shift() const { assert(_type == ExpressionType::Shift); return *_shift; }
		const AdditiveExpression& additive() const { assert(_type == ExpressionType::Additive); return *_additive; }
		const MultiplicativeExpression& multiplicative() const { assert(_type == ExpressionType::Multiplicative); return *_multiplicative; }
		const PrefixExpression& prefix() const { assert(_type == ExpressionType::Prefix); return *_prefix; }
		const PostfixExpression& postfix() const { assert(_type == ExpressionType::Postfix); return *_postfix; }
		const PrimaryExpression& primary() const { assert(_type == ExpressionType::Primary); return *_primary; }
		const Constant& constant() const { assert(_type == ExpressionType::Constant); return *_constant; }
		const Symbol& symbol() const { assert(_type == ExpressionType::Symbol); return *_symbol; }
	};
}

#endif
