#ifndef WARBLER_AST_TYPENAME_HPP
#define WARBLER_AST_TYPENAME_HPP

// local headers
#include <cassert>
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/ast/type/type_definition.hpp>

namespace warbler::ast
{
	class Typename
	{
	private:

		Location _location;
		String _name;
		Array<bool> _ptr_mutability;
		TypeDefinition *_definition;

	public:

		Typename();
		Typename(const Location& location, Array<bool>&& ptr_mutability);

		static Result<Typename> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		bool validate_cast_from(semantics::ModuleContext& context, const Typename& other);
		void print_tree(u32 depth = 0) const;

		const Location& location() const { return _location; }
		const String& name() const { return _name; }
		const Array<bool>& ptr_mutability() const { return _ptr_mutability; }
		TypeDefinition& definition() { assert(_definition != nullptr); return *_definition; }
		u32 reference_depth() const { return _ptr_mutability.size(); }
	};
}

#endif
