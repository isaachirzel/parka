#include <warbler/syntax/expression/expression.hpp>

#include <warbler/syntax/expression/symbol.hpp>
#include <warbler/syntax/expression/constant.hpp>
#include <warbler/syntax/expression/primary_expression.hpp>
#include <warbler/syntax/expression/postfix_expression.hpp>
#include <warbler/syntax/expression/prefix_expression.hpp>
#include <warbler/syntax/expression/multiplicative_expression.hpp>
#include <warbler/syntax/expression/additive_expression.hpp>
#include <warbler/syntax/expression/shift_expression.hpp>
#include <warbler/syntax/expression/relational_expression.hpp>
#include <warbler/syntax/expression/equality_expression.hpp>
#include <warbler/syntax/expression/bitwise_and_expression.hpp>
#include <warbler/syntax/expression/bitwise_xor_expression.hpp>
#include <warbler/syntax/expression/bitwise_or_expression.hpp>
#include <warbler/syntax/expression/boolean_and_expression.hpp>
#include <warbler/syntax/expression/boolean_or_expression.hpp>
#include <warbler/syntax/expression/conditional_expression.hpp>

namespace warbler::syntax
{
	Expression::Expression(ConditionalExpression&& conditional) :
	_conditional(new ConditionalExpression(std::move(conditional))),
	_type(ExpressionType::Conditional)
	{}

	Expression::Expression(BooleanOrExpression&& boolean_or) :
	_boolean_or(new BooleanOrExpression(std::move(boolean_or))),
	_type(ExpressionType::BooleanOr)
	{}

	Expression::Expression(BooleanAndExpression&& boolean_and) :
	_boolean_and(new BooleanAndExpression(std::move(boolean_and))),
	_type(ExpressionType::BooleanAnd)
	{}

	Expression::Expression(BitwiseOrExpression&& bitwise_or) :
	_bitwise_or(new BitwiseOrExpression(std::move(bitwise_or))),
	_type(ExpressionType::BitwiseOr)
	{}

	Expression::Expression(BitwiseXorExpression&& bitwise_xor) :
	_bitwise_xor(new BitwiseXorExpression(std::move(bitwise_xor))),
	_type(ExpressionType::BitwiseXor)
	{}

	Expression::Expression(BitwiseAndExpression&& bitwise_and) :
	_bitwise_and(new BitwiseAndExpression(std::move(bitwise_and))),
	_type(ExpressionType::BitwiseAnd)
	{}

	Expression::Expression(EqualityExpression&& equality) :
	_equality(new EqualityExpression(std::move(equality))),
	_type(ExpressionType::Equality)
	{}

	Expression::Expression(RelationalExpression&& relational) :
	_relational(new RelationalExpression(std::move(relational))),
	_type(ExpressionType::Relational)
	{}

	Expression::Expression(ShiftExpression&& shift) :
	_shift(new ShiftExpression(std::move(shift))),
	_type(ExpressionType::Shift)
	{}

	Expression::Expression(AdditiveExpression&& additive) :
	_additive(new AdditiveExpression(std::move(additive))),
	_type(ExpressionType::Additive)
	{}

	Expression::Expression(MultiplicativeExpression&& multiplicative) :
	_multiplicative(new MultiplicativeExpression(std::move(multiplicative))),
	_type(ExpressionType::Multiplicative)
	{}

	Expression::Expression(PrefixExpression&& prefix) :
	_prefix(new PrefixExpression(std::move(prefix))),
	_type(ExpressionType::Prefix)
	{}

	Expression::Expression(PostfixExpression&& postfix) :
	_postfix(new PostfixExpression(std::move(postfix))),
	_type(ExpressionType::Postfix)
	{}

	Expression::Expression(PrimaryExpression&& primary) :
	_primary(new PrimaryExpression(std::move(primary))),
	_type(ExpressionType::Primary)
	{}

	Expression::Expression(Constant&& constant) :
	_constant(new Constant(std::move(constant))),
	_type(ExpressionType::Constant)
	{}

	Expression::Expression(Symbol&& symbol) :
	_symbol(new Symbol(std::move(symbol))),
	_type(ExpressionType::Symbol)
	{}

	Expression::Expression(Expression&& other) :
	_type(other._type)
	{
		switch (_type)
		{
		case ExpressionType::Conditional:
			_conditional = other._conditional;
			other._conditional = nullptr;
			break;
		case ExpressionType::BooleanOr:
			_boolean_or = other._boolean_or;
			other._boolean_or = nullptr;
			break;
		case ExpressionType::BooleanAnd:
			_boolean_and = other._boolean_and;
			other._boolean_and = nullptr;
			break;
		case ExpressionType::BitwiseOr:
			_bitwise_or = other._bitwise_or;
			other._bitwise_or = nullptr;
			break;
		case ExpressionType::BitwiseXor:
			_bitwise_xor = other._bitwise_xor;
			other._bitwise_xor = nullptr;
			break;
		case ExpressionType::BitwiseAnd:
			_bitwise_and = other._bitwise_and;
			other._bitwise_and = nullptr;
			break;
		case ExpressionType::Equality:
			_equality = other._equality;
			other._equality = nullptr;
			break;
		case ExpressionType::Relational:
			_relational = other._relational;
			other._relational = nullptr;
			break;
		case ExpressionType::Shift:
			_shift = other._shift;
			other._shift = nullptr;
			break;
		case ExpressionType::Additive:
			_additive = other._additive;
			other._additive = nullptr;
			break;
		case ExpressionType::Multiplicative:
			_multiplicative = other._multiplicative;
			other._multiplicative = nullptr;
			break;
		case ExpressionType::Postfix:
			_prefix = other._prefix;
			other._prefix = nullptr;
			break;
		case ExpressionType::Prefix:
			_postfix = other._postfix;
			other._postfix = nullptr;
			break;
		case ExpressionType::Primary:
			_primary = other._primary;
			other._primary = nullptr;
			break;
		case ExpressionType::Constant:
			_constant = other._constant;
			other._constant = nullptr;
			break;
		case ExpressionType::Symbol:
			_symbol = other._symbol;
			other._symbol = nullptr;
			break;
		}
	}

	Expression::~Expression()
	{
		switch (_type)
		{
		case ExpressionType::Conditional:
			delete _conditional;
			break;
		case ExpressionType::BooleanOr:
			delete _boolean_or;
			break;
		case ExpressionType::BooleanAnd:
			delete _boolean_and;
			break;
		case ExpressionType::BitwiseOr:
			delete _bitwise_or;
			break;
		case ExpressionType::BitwiseXor:
			delete _bitwise_xor;
			break;
		case ExpressionType::BitwiseAnd:
			delete _bitwise_and;
			break;
		case ExpressionType::Equality:
			delete _equality;
			break;
		case ExpressionType::Relational:
			delete _relational;
			break;
		case ExpressionType::Shift:
			delete _shift;
			break;
		case ExpressionType::Additive:
			delete _additive;
			break;
		case ExpressionType::Multiplicative:
			delete _multiplicative;
			break;
		case ExpressionType::Postfix:
			delete _prefix;
			break;
		case ExpressionType::Prefix:
			delete _postfix;
			break;
		case ExpressionType::Primary:
			delete _primary;
			break;
		case ExpressionType::Constant:
			delete _constant;
			break;
		case ExpressionType::Symbol:
			delete _symbol;
			break;
		}
	}

	Result<Expression> Expression::parse(lexicon::Token& token)
	{
		return ConditionalExpression::parse(token);
	}
}
