#ifndef WARBLER_SYNTAX_DECLARATION_HPP
#define WARBLER_SYNTAX_DECLARATION_HPP

#include <warbler/syntax/identifier.hpp>
#include <warbler/syntax/type.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/util/optional.hpp>

namespace warbler::syntax
{
	class Declaration
	{
	private:

		Identifier _name;
		Optional<Type> _type;
		bool _is_mutable;

	public:

		Declaration(Identifier&& name, Optional<Type>&& type, bool is_mutable);

		static Result<Declaration> parse_parameter(lexicon::Token& token);
		static Result<Declaration> parse_variable(lexicon::Token& token);

		bool validate_variable(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		bool validate_parameter(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		bool is_mutable() const { return _is_mutable; }
		bool is_auto_type() const { return _type.has_value(); }
		const Identifier& name() const { return _name; }
		Type& type() { return *_type; }
	};
}

#endif
