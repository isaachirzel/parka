#ifndef WARBLER_SYNTAX_TYPE_TYPE_DEFINITION_HPP
#define WARBLER_SYNTAX_TYPE_TYPE_DEFINITION_HPP

#include <warbler/semantics/context.hpp>
#include <warbler/syntax/type/type_definition.hpp>
#include <warbler/syntax/identifier.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::syntax
{
	struct TypeDefinition
	{
		virtual ~TypeDefinition() {}

		static Result<Ptr<TypeDefinition>> parse(lexicon::Token& token);

		virtual bool validate(semantics::Context& context) = 0;
		virtual const Identifier& name() const = 0;
	};
}

#endif
