#ifndef WARBLER_AST_DECLARATION_HPP
#define WARBLER_AST_DECLARATION_HPP

#include <warbler/ast/identifier.hpp>
#include <warbler/ast/type.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Declaration
	{
	private:

		Identifier _name;
		Type _type;
		bool _is_mutable;

	public:

		Declaration(Identifier&& name, Type&& type, bool is_mutable);

		static Result<Declaration> parse_parameter(TokenIterator& iter);
		static Result<Declaration> parse_variable(TokenIterator& iter);

		bool validate_variable(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		bool validate_parameter(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		bool is_mutable() const { return _is_mutable; }
		const Identifier& name() const { return _name; }
		Type& type() { return _type; }
	};
}

#endif
