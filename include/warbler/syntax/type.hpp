#ifndef WARBLER_SYNTAX_TYPENAME_HPP
#define WARBLER_SYNTAX_TYPENAME_HPP

// local headers
#include <cassert>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/syntax//type/type_definition.hpp>

namespace warbler::syntax
{
	class Type
	{
	private:

		Location _location;
		String _base_name;
		Array<bool> _ptr_mutability;
		TypeDefinition *_definition = nullptr;
		bool _is_auto = true;

	public:

		Type();
		Type(const Location& location, String&& base_name, Array<bool>&& ptr_mutability);
		Type(String&& base_name, TypeDefinition *_definition);

		static Result<Type> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		bool validate_cast_from(Type* other);
		void print_tree(u32 depth = 0) const;

		const Location& location() const { return _location; }
		String text() const;
		const String& base_name() const { return _base_name; }
		const Array<bool>& ptr_mutability() const { return _ptr_mutability; }
		TypeDefinition *definition() { assert(_definition != nullptr); return _definition; }
		u32 reference_depth() const { return _ptr_mutability.size(); }
		bool is_auto() const { return _is_auto; }
	};
}

#endif
