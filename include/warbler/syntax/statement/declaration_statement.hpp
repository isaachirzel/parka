#ifndef WARBLER_SYNTAX_STATEMENT_DECLARATION_STATEMENT_HPP
#define WARBLER_SYNTAX_STATEMENT_DECLARATION_STATEMENT_HPP

// local headers
#include <warbler/syntax/statement/declaration.hpp>
#include <warbler/syntax/expression/conditional_expression.hpp>
#include <warbler/syntax/statement/statement.hpp>

namespace warbler::syntax
{
	class DeclarationStatement : public Statement
	{
	private:

		Declaration _declaration;
		Ptr<Expression> _value;

	public:

		DeclarationStatement(Declaration&& declaration, Ptr<Expression>&& value);
		DeclarationStatement(DeclarationStatement&&) = default;
		DeclarationStatement(const DeclarationStatement&) = delete;

		static Result<DeclarationStatement> parse(lexicon::Token& token);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
