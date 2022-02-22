#ifndef WARBLER_AST_EXPRESSION_POSTFIX_EXRESSION
#define WARBLER_AST_EXPRESSION_POSTFIX_EXRESSION

#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/identifier.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::ast
{
	enum PostfixType
	{
		POSTFIX_INDEX,
		POSTFIX_FUNCTION_CALL,
		POSTFIX_MEMBER
	};

	class PostfixExpression : public Expression
	{
	private:

		Ptr<Expression> _expression;

		union
		{
			Ptr<Expression> _index;
			Array<Ptr<Expression>> _arguments;
			Identifier _member;
		};

		PostfixType _type;

	public:

		PostfixExpression(Ptr<Expression>&& expression, Ptr<Expression>&& index);
		PostfixExpression(Ptr<Expression>&& expression, Array<Ptr<Expression>>&& arguments);
		PostfixExpression(Ptr<Expression>&& expression, Identifier&& member);
		PostfixExpression(PostfixExpression&& other);
		PostfixExpression(const PostfixExpression& other) = delete;
		~PostfixExpression();
		
		static Result<Ptr<Expression>> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& module, semantics::FunctionContext& function);
		Typename *get_type(semantics::ModuleContext& module) const;
		const Location& location() const;
		void print_tree(u32 depth = 0) const;
	};
}

#endif
