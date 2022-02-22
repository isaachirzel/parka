#ifndef WARBLER_AST_TYPE_TYPE_HPP
#define WARBLER_AST_TYPE_TYPE_HPP

#include <warbler/ast/identifier.hpp>
#include <warbler/ast/type/type_definition.hpp>

#include <warbler/semantics/context.hpp>
#include <warbler/token.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::ast
{
	class Type
	{
	private:

		Identifier _name;
		Ptr<TypeDefinition> _definition;
		semantics::TypeContext _context;

	public:

		Type(Identifier&& name, Ptr<TypeDefinition>&& definition);
		Type(Type&&) = default;
		Type(const Type&) = delete;

		static Result<Type> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx);
		void print_tree(u32 depth = 0) const;

		const Identifier& name() const { return _name; }
		const TypeDefinition& definition() const { return *_definition; }
	};
}

#endif
