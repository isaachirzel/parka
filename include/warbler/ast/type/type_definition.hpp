#ifndef WARBLER_AST_TYPE_DEFINITION_HPP
#define WARBLER_AST_TYPE_DEFINITION_HPP

// local headers
#include <warbler/ast/identifier.hpp>
#include <warbler/ast/type/struct.hpp>
#include <warbler/ast/type/enum.hpp>

namespace warbler::semantics
{
	class Context;
}

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

		Identifier _name;

		union
		{
			Struct _struct;
			Enum _enum;
		};

		TypeDefinitionType _type;

	public:

		TypeDefinition(Identifier&& name, Struct&& struct_def);
		TypeDefinition(Identifier&& name, Enum&& enum_def);
		TypeDefinition(TypeDefinition&& other);
		TypeDefinition(const TypeDefinition& other);
		~TypeDefinition();

		static Result<TypeDefinition> parse(TokenIterator& iter);

		void validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;

		TypeDefinition& operator=(TypeDefinition&& other);
		TypeDefinition& operator=(const TypeDefinition& other);
	};
}

#endif
