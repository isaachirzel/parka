#ifndef WARBLER_SYNTAX_EXPRESSION_POSTFIX_EXRESSION
#define WARBLER_SYNTAX_EXPRESSION_POSTFIX_EXRESSION

#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/identifier.hpp>
#include <warbler/util/ptr.hpp>

namespace warbler::syntax
{
	enum PostfixType
	{
		POSTFIX_INDEX,
		POSTFIX_FUNCTION_CALL,
		POSTFIX_MEMBER
	};

	struct MemberExpression
	{
		Identifier name;
		Member *definition;
	};

	class PostfixExpression : public Expression
	{
	private:

		Ptr<Expression> _expression;

		union
		{
			Ptr<Expression> _index;
			Array<Ptr<Expression>> _arguments;
			MemberExpression _member;
		};

		PostfixType _type;

	public:

		PostfixExpression(Ptr<Expression>&& expression, Ptr<Expression>&& index);
		PostfixExpression(Ptr<Expression>&& expression, Array<Ptr<Expression>>&& arguments);
		PostfixExpression(Ptr<Expression>&& expression, Identifier&& member_name);
		PostfixExpression(PostfixExpression&& other);
		PostfixExpression(const PostfixExpression& other) = delete;
		~PostfixExpression();
		
		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& module, semantics::FunctionContext& function);
		Type *get_type();
		const source::Location& location() const;
		void print_tree(u32 depth = 0) const;
	};
}

#endif
