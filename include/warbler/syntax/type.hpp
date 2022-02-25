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
	class Type
	{
	private:

		source::Location _location;
		source::Location _base_type_location;
		Array<bool> _ptr_mutability;

	public:

		Type();
		Type(const source::Location& location, String&& base_name, Array<bool>&& ptr_mutability);
		Type(String&& base_name, TypeDefinition *_definition);

		static Result<Type> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		bool validate_cast_from(Type* other);
		void print_tree(u32 depth = 0) const;

		const source::Location& location() const { return _location; }
		const source::Location& base_type_location() const { return _base_type_location; }
		const Array<bool>& ptr_mutability() const { return _ptr_mutability; }
	};
}

#endif
