#ifndef WARBLER_SYNTAX_FUNCTION_HPP
#define WARBLER_SYNTAX_FUNCTION_HPP

// local headers
#include <warbler/syntax/identifier.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/expression/conditional_expression.hpp>
#include <warbler/syntax/statement/block_statement.hpp>
#include <warbler/syntax/statement/statement.hpp>
#include <warbler/syntax/function/parameter.hpp>
#include <warbler/util/table.hpp>
#include <warbler/util/optional.hpp>
#include <warbler/syntax/function/function_signature.hpp>

namespace warbler::syntax
{
	class Function
	{
	private:

		Identifier _name;
		FunctionSignature _signature;
		BlockStatement _body;
	
	public:

		Function(Identifier&& name, FunctionSignature&& signature, BlockStatement&& compound_body);
		Function(Function&& other) = default;
		Function(const Function& other) = delete;		

		static Result<Function> parse(lexicon::Token& token);

		void print_tree(u32 depth = 0) const;
		bool validate(semantics::Context& context);

		const Identifier& name() const { return _name; }

		Function& operator=(Function&& other) = default;
		Function& operator=(const Function& other) = delete;
	};
}

#endif
