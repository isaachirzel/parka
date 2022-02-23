#ifndef WARBLER_SYNTAX_ARGUMENT_HPP
#define WARBLER_SYNTAX_ARGUMENT_HPP

// standard headers
#include <warbler/util/result.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/syntax//expression/expression.hpp>

namespace warbler::syntax
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

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		Argument& operator=(Argument&& other) = default;
		Argument& operator=(const Argument& other) = delete;
	};
}

#endif
