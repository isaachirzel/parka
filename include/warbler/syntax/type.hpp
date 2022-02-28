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
	struct PtrLocation
	{
		source::Location location;
		bool is_mutable;
	};

	class Type
	{
	private:

		source::Location _base_type;
		Array<PtrLocation> _ptrs;

	public:

		Type(const source::Location& base_type, Array<PtrLocation>&& ptrs);

		static Result<Type> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		bool validate_cast_from(Type* other);
		void print_tree(u32 depth = 0) const;

		const source::Location& base_type() const { return _base_type; }
		const Array<PtrLocation>& ptrs() const { return _ptrs; }
	};
}

#endif
