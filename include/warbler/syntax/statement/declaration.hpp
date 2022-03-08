#ifndef WARBLER_SYNTAX_DECLARATION_HPP
#define WARBLER_SYNTAX_DECLARATION_HPP

#include <warbler/syntax/identifier.hpp>
#include <warbler/syntax/type.hpp>
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

		static Result<Declaration> parse(lexicon::Token& token);

		bool validate_variable(semantics::Context& context);

		bool is_mutable() const { return _is_mutable; }
		bool is_auto_type() const { return _type.has_value(); }

		const Identifier& name() const { return _name; }
		Type& type() { return *_type; }
	};
}

#endif
