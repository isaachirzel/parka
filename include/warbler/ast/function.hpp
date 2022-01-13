#ifndef WARBLER_AST_FUNCTION_HPP
#define WARBLER_AST_FUNCTION_HPP

// local headers
#include <warbler/ast/typename.hpp>
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/parameter.hpp>
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/statement/statement.hpp>
#include <warbler/ast/statement/compound_statement.hpp>

namespace warbler
{
	class Function
	{
	private:

		Identifier _name;
		std::vector<Parameter> _parameters;
		Typename _return_type;

		union
		{
			Expression *_inline_body;
			std::vector<Statement> _compound_body;
		};
		
		bool _is_inline;
	
	public:

		Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, Expression *inline_body);
		Function(Identifier&& name, std::vector<Parameter>&& parameters, Typename&& return_type, std::vector<Statement>&& compound_body);
		Function(Function&& other);
		Function(const Function& other);
		~Function();

		static Result<Function> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
