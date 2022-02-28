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

	class PrefixExpression : public Expression
	{
	private:

		source::Location _location;
		Ptr<Expression> _expression;
		PrefixType _type;

	public:

		PrefixExpression(const source::Location& location, Ptr<Expression>&& expression, PrefixType type);

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& module, semantics::FunctionContext& function);
		Type *get_type();
		const source::Location& location() const { return _location; }
		void print_tree(u32 depth = 0) const;
	};
}

#endif