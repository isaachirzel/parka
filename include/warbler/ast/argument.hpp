#ifndef WARBLER_AST_ARGUMENT_HPP
#define WARBLER_AST_ARGUMENT_HPP

// standard headers
#include <warbler/util/result.hpp>
#include <warbler/token.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	class Argument
	{
	private:

		Ptr<Expression> _expr;

	public:

		Argument(Ptr<Expression>&& expr);
		Argument(Argument&&) = default;
		Argument(const Argument&) = delete;

		static Result<Argument> parse(TokenIterator& iter);
		static Result<std::vector<Argument>> parse_list(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		void print_tree(u32 depth = 0) const;

		Argument& operator=(Argument&& other) = default;
		Argument& operator=(const Argument& other) = delete;
	};
}

#endif
