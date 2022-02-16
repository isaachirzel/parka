#ifndef WARBLER_AST_TYPENAME_HPP
#define WARBLER_AST_TYPENAME_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Typename
	{
	private:

		Location _location;
		String _name;
		u32 _reference_depth;

	public:

		Typename();
		Typename(const Location& location, String&& name);

		static Result<Typename> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		void print_tree(u32 depth = 0) const;
		bool validate();

		const Location& location() const { return _location; }
		const String& name() const { return _name; }
		u32 reference_depth() const { return _reference_depth; }
	};
}

#endif
