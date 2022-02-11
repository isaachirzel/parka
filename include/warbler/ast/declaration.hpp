#ifndef WARBLER_AST_DECLARATION_HPP
#define WARBLER_AST_DECLARATION_HPP

#include <warbler/ast/identifier.hpp>
#include <warbler/ast/typename.hpp>

namespace warbler::ast
{
	class Declaration
	{
	private:

		bool _is_mutable;
		Identifier _name;
		Typename _type;

	public:

		Declaration(bool is_mutable, Identifier&& name, Typename&& type);

		static Result<Declaration> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& module_context, semantics::FunctionContext& function_context);
		void print_tree(u32 depth = 0) const;

		bool is_mutable() const { return _is_mutable; }
		Identifier name() const { return _name; }
		Typename type() const { return _type; }
	};
}

#endif
