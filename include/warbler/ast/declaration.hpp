#ifndef WARBLER_AST_DECLARATION_HPP
#define WARBLER_AST_DECLARATION_HPP

#include <warbler/ast/name.hpp>
#include <warbler/ast/typename.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Declaration
	{
	private:

		Name _name;
		Typename _type;
		bool _is_mutable;

	public:

		Declaration(Name&& name, Typename&& type, bool is_mutable);

		static Result<Declaration> parse_parameter(TokenIterator& iter);
		static Result<Declaration> parse_variable(TokenIterator& iter);

		bool validate_variable(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		bool validate_parameter(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		bool is_mutable() const { return _is_mutable; }
		const Name& name() const { return _name; }
		const Typename& type() const { return _type; }
	};
}

#endif
