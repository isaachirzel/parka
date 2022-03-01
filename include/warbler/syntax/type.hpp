#ifndef WARBLER_SYNTAX_TYPENAME_HPP
#define WARBLER_SYNTAX_TYPENAME_HPP

// local headers
#include <cassert>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/syntax/type/type_definition.hpp>

namespace warbler::syntax
{
	struct PtrToken
	{
		lexicon::Token token;
		bool is_mutable;
	};

	class Type
	{
	private:

		lexicon::Token _base_type;
		Array<PtrToken> _ptrs;

	public:

		Type(const lexicon::Token& base_type, Array<PtrToken>&& ptrs);

		static Result<Type> parse(lexicon::Token& token);

		bool validate(semantics::ModuleContext& context);
		bool validate_cast_from(Type* other);
		void print_tree(u32 depth = 0) const;

		const lexicon::Token& base_type() const { return _base_type; }
		const Array<PtrToken>& ptrs() const { return _ptrs; }
	};
}

#endif
