#ifndef WARBLER_SYNTAX_EXPRESSION_POSTFIX_EXRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_POSTFIX_EXRESSION_HPP

#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/identifier.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::syntax
{
	enum class PostfixType
	{
		Index,
		FunctionCall,
		Member
	};

	class PostfixExpression
	{
	private:

		Expression _expression;

		union
		{
			Expression _index;
			Array<Expression> _arguments;
			Identifier _member;
		};

		PostfixType _type;

	public:

		PostfixExpression(Expression&& expression, Expression&& index);
		PostfixExpression(Expression&& expression, Array<Expression>&& arguments);
		PostfixExpression(Expression&& expression, Identifier&& member);
		PostfixExpression(PostfixExpression&& other);
		PostfixExpression(const PostfixExpression& other) = delete;
		~PostfixExpression();
		
		static Result<Expression> parse(lexicon::Token& token);

		
		Type *get_type();
		const lexicon::Token& token() const;
		void print_tree(u32 depth = 0) const;
	};
}

#endif
