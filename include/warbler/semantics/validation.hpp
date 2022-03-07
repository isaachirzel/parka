#ifndef WARBLER_SEMANTICS_VALIDATION_HPP
#define WARBLER_SEMANTICS_VALIDATION_HPP

#include <warbler/util/string.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/table.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

#include <warbler/syntax/ast.hpp>

namespace warbler::semantics
{
	struct Identifier
	{
	};

	struct TypeDefinition
	{
		virtual ~TypeDefinition() = default;
		virtual u32 id() const = 0;
	};

	// struct Struct : public TypeDefinition
	// {
	// 	u32 _id;
	// 	u32 id() const;
	// };

	// struct Primitive : public TypeDefinition
	// {
	// 	u32 _id;
	// 	u32 id() const;
	// };

	struct Type
	{
		u32 type_id;
		Array<bool> ptr_mutability;
	};

	struct Statement
	{
		virtual ~Statement() = default;
	};

	struct BlockStatement : public Statement
	{
		Array<Ptr<Statement>> statements;
	};

	struct Parameter
	{
		bool is_mutable;
		Identifier name;
		Type type;
	};

	struct FunctionSignature
	{
		Array<Parameter> parameters;
		u32 return_type_id;
	};

	struct Function
	{
		String symbol;
		FunctionSignature signature;
		BlockStatement body;
	};

	struct Module
	{
		Table<Ptr<TypeDefinition>> types;
		Table<Function> functions;

	};

	struct Svt
	{
		Module _module;
	};

	Result<Module> validate(const syntax::Module& syntax);
	Result<Svt> validate(const syntax::Ast& syntax);
}

#endif
