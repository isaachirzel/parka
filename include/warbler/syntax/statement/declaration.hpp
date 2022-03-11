#ifndef WARBLER_SYNTAX_DECLARATION_HPP
#define WARBLER_SYNTAX_DECLARATION_HPP

#include <warbler/syntax/identifier.hpp>
#include <warbler/syntax/type.hpp>
#include <warbler/util/optional.hpp>

namespace warbler::syntax
{
	class Variable
	{
	private:

		Identifier _name;
		Optional<Type> _type;
		bool _is_mutable;

	public:

		Variable(Identifier&& name, Optional<Type>&& type, bool is_mutable);

		static Result<Variable> parse(lexicon::Token& token);

		bool is_mutable() const { return _is_mutable; }
		bool is_auto_type() const { return _type.has_value(); }

		const Identifier& name() const { return _name; }
		Type& type() { return *_type; }
	};
}

#endif
