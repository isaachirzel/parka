#ifndef WARBLER_AST_FUNCTION_HPP
#define WARBLER_AST_FUNCTION_HPP

// local headers
#include <warbler/ast/typename.hpp>
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/parameter.hpp>
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/ast/statement/statement.hpp>
#include <warbler/util/table.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Symbol;

	class Function
	{
	private:

		Identifier _name;
		Array<Parameter> _parameters;
		Typename _return_type;

		union
		{
			Expression _inline_body;
			Array<Statement> _compound_body;
		};
		
		bool _is_inline;
	
	public:

		Function(Identifier&& name, Array<Parameter>&& parameters, Typename&& return_type, Expression&& inline_body);
		Function(Identifier&& name, Array<Parameter>&& parameters, Typename&& return_type, Array<Statement>&& compound_body);
		Function(Function&& other);
		Function(const Function& other);
		~Function();

		static Result<Function> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
		bool validate(semantics::Context& context);

		const Identifier& name() const { return _name; }

		Function& operator=(Function&& other);
		Function& operator=(const Function& other);
	};
}

#endif
