#ifndef WARBLER_SYNTAX_EXPRESSION_PREFIX_EXRESSION
#define WARBLER_SYNTAX_EXPRESSION_PREFIX_EXRESSION

#include <warbler/syntax//expression/postfix_expression.hpp>

namespace warbler::syntax
{
	enum PrefixType
	{
		PREFIX_REFERENCE,
		PREFIX_DEREFERENCE,
		PREFIX_POSITIVE,
		PREFIX_NEGATIVE,
		PREFIX_BITWISE_NOT,
		PREFIX_BOOLEAN_NOT
	};

	class PrefixExpression : public Expression
	{
	private:

		Ptr<Expression> _expression;
		PrefixType _type;

	public:

		PrefixExpression(Ptr<Expression>&& expression, PrefixType type);

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& module, semantics::FunctionContext& function);
		Type *get_type();
		const source::Location& location() const;
		void print_tree(u32 depth = 0) const;
	};
}

#endif