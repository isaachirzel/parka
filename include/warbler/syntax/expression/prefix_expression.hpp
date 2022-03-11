#ifndef WARBLER_SYNTAX_EXPRESSION_PREFIX_EXRESSION
#define WARBLER_SYNTAX_EXPRESSION_PREFIX_EXRESSION

#include <warbler/syntax/expression/postfix_expression.hpp>

namespace warbler::syntax
{
	enum class PrefixType
	{
		Reference,
		Dereference,
		Positive,
		Negative,
		BitwiseNot,
		BooleanNot
	};

	class PrefixExpression
	{
	private:

		lexicon::Token _token;
		Expression _expression;
		PrefixType _type;

	public:

		PrefixExpression(const lexicon::Token& token, Expression&& expression, PrefixType type);

		static Result<Expression> parse(lexicon::Token& token);

		
		Type *get_type();
		const lexicon::Token& token() const { return _token; }
		void print_tree(u32 depth = 0) const;
	};
}

#endif