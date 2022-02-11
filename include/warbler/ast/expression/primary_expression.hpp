#ifndef WARBLER_AST_PRIMARY_EXPRESSION_HPP
#define WARBLER_AST_PRIMARY_EXPRESSION_HPP

// local headers
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/expression/constant.hpp>
#include <warbler/ast/expression/prefix.hpp>
#include <warbler/ast/expression/postfix.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	enum PrimaryType
	{
		PRIMARY_IDENTIFIER,
		PRIMARY_CONSTANT,
		PRIMARY_EXPRESSION
	};

	class PrimaryExpression
	{
	private:

		Array<Prefix> _prefixes;
		Array<Postfix> _postfixes;

		union
		{
			Identifier _identifier;
			Constant _constant;
			Ptr<Expression> _expression;
		};

		PrimaryType _type;
	
	public:

		PrimaryExpression() = delete;
		PrimaryExpression(Array<Prefix>&& prefixes, Array<Postfix>&& postfixes, Identifier&& identifier);
		PrimaryExpression(Array<Prefix>&& prefixes, Array<Postfix>&& postfixes, Constant&& constant);
		PrimaryExpression(Array<Prefix>&& prefixes, Array<Postfix>&& postfixes, Ptr<Expression>&& expression);
		PrimaryExpression(PrimaryExpression&& other);
		PrimaryExpression(const PrimaryExpression&) = delete;
		~PrimaryExpression();

		static Result<PrimaryExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context, bool expect_lvalue = false);
		void print_tree(u32 depth = 0) const;

		PrimaryExpression& operator=(PrimaryExpression&& other);
		PrimaryExpression& operator=(const PrimaryExpression&) = delete;
	};
}
#endif
