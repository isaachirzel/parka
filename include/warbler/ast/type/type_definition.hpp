#ifndef WARBLER_AST_TYPE_DEFINITION_HPP
#define WARBLER_AST_TYPE_DEFINITION_HPP

// local headers
#include <warbler/ast/name.hpp>
#include <warbler/ast/type/struct.hpp>
#include <warbler/ast/type/enum.hpp>
#include <warbler/ast/type/type_definition_body.hpp>

namespace warbler::ast
{
	enum TypeDefinitionType
	{
		DEFINITION_STRUCT,
		DEFINITION_ENUM
	};

	class TypeDefinition
	{
	private:

		Name _name;
		String _symbol;
		TypeDefinitionBody *_body;

	public:

		TypeDefinition(Name&& name, TypeDefinitionBody *body);
		TypeDefinition(TypeDefinition&&);
		TypeDefinition(const TypeDefinition&) = delete;
		~TypeDefinition();

		static Result<TypeDefinition> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		const String& generate_symbol(semantics::ModuleContext& contetxt);
		void print_tree(u32 depth = 0) const;

		const Name& name() const { return _name; }
		const String& symbol() const { return _symbol; }

		TypeDefinition& operator=(TypeDefinition&& other);
		TypeDefinition& operator=(const TypeDefinition& other) = delete;
	};
}

#endif
