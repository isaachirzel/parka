#ifndef WARBLER_SYNTAX_FUNCTION_HPP
#define WARBLER_SYNTAX_FUNCTION_HPP

// local headers
#include <warbler/syntax//identifier.hpp>
#include <warbler/syntax//expression/expression.hpp>
#include <warbler/syntax//expression/conditional_expression.hpp>
#include <warbler/syntax//statement/block_statement.hpp>
#include <warbler/syntax//statement/statement.hpp>
#include <warbler/syntax//declaration.hpp>
#include <warbler/util/table.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::syntax
{
	class Symbol;

	class Function
	{
	private:

		semantics::FunctionContext _context;
		Identifier _name;
		Array<Declaration> _parameters;
		Type _return_type;
		BlockStatement _body;
	
	public:

		Function(Identifier&& name, Array<Declaration>&& parameters, Type&& return_type, BlockStatement&& compound_body);
		Function(Function&& other) = default;
		Function(const Function& other) = delete;		

		static Result<Function> parse(lexicon::TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
		bool validate(semantics::ModuleContext& context);

		const Identifier& name() const { return _name; }

		Function& operator=(Function&& other) = default;
		Function& operator=(const Function& other) = delete;
	};
}

#endif
