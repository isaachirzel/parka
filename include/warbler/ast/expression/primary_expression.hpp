#ifndef WARBLER_AST_PRIMARY_EXPRESSION_HPP
#define WARBLER_AST_PRIMARY_EXPRESSION_HPP

// local headers
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/expression/constant.hpp>
#include <warbler/ast/expression/prefix.hpp>
#include <warbler/ast/expression/postfix.hpp>

namespace warbler
{
	class Expression;

	enum PrimaryType
	{
		PRIMARY_IDENTIFIER,
		PRIMARY_CONSTANT,
		PRIMARY_EXPRESSION
	};

	class PrimaryExpression
	{
	private:

		std::vector<Prefix> _prefixes;
		std::vector<Postfix> _postfixes;

		union
		{
			Identifier _identifier;
			Constant _constant;
			Expression *_expression;
		};

		PrimaryType _type;
	
	public:

		PrimaryExpression(std::vector<Prefix>&& prefixes, std::vector<Postfix>&& postfixes, Identifier&& identifier);
		PrimaryExpression(std::vector<Prefix>&& prefixes, std::vector<Postfix>&& postfixes, Constant&& constant);
		PrimaryExpression(std::vector<Prefix>&& prefixes, std::vector<Postfix>&& postfixes, Expression *expression);
		PrimaryExpression(PrimaryExpression&& other);
		PrimaryExpression(const PrimaryExpression& other);
		~PrimaryExpression();

		static Result<PrimaryExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}
#endif
