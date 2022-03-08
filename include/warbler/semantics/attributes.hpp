#ifndef WARBLER_SEMANTICS_ATTRIBUTES
#define WARBLER_SEMANTICS_ATTRIBUTES

#include <warbler/util/primitive.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/optional.hpp>
#include <cassert>

namespace warbler::semantics
{
	enum class Mutability
	{
		Mutable,
		Immutable
	};

	class Type
	{
	private:

		Array<Mutability> _ptr_mutability;
		u32 _base_type_id;

	public:

		Type(const Array<bool>& ptr_info, u32 _base_type_id);

		bool can_cast_from(const Type& other);
	};


	struct Primitive
	{
		u32 _primitive_id;
	};

	struct Member
	{
		bool is_public;
		Type type;
	};

	class Struct
	{
		Table<Member> _members;
	};

	enum class DefinitionType
	{
		Primitive,
		Struct
	};

	class Definition
	{
		union
		{
			Struct _struct_def;
			Primitive _primitive_def;
		};

		DefinitionType _type;

	public:

		Definition(Struct&& struct_def);
		Definition(Primitive&& primitive_def);
		Definition(Definition&& other);
		Definition(const Definition&) = delete;
		~Definition();

		DefinitionType type() const { return _type; }
		Struct& struct_def() { assert(_type == DefinitionType::Struct); return _struct_def; }
		Primitive& primitive_def() { assert(_type == DefinitionType::Primitive); return _primitive_def; }
	};

	enum class ParameterState
	{
		Valid,
		Invalid
	};

	struct ParameterContext
	{
		Type type;
		ParameterState state;
		bool _is_mutable;

		ParameterContext(Type&& type, ParameterState state);
	};

	enum class VariableState
	{
		Declared,
		Defined,
		Invalid
	};

	struct VariableContext
	{
		Optional<Type> type;
		VariableState  state;
		bool _is_mutable;

		VariableContext(Optional<Type>&& type, VariableState state);
	};

	struct FunctionContext
	{
		Array<ParameterContext> parameters;
		Type return_type;

		FunctionContext(Array<ParameterContext>&& parameters, Type&& return_type);
	};

	enum class SymbolType
	{
		Function,
		Parameter,
		Variable
	};

	struct SymbolContext
	{
	private:

		union
		{
			VariableContext _variable;
			ParameterContext _parameter;
			FunctionContext _function;
		};

		SymbolType _type;

	public:

		SymbolContext(VariableContext&& variable);
		SymbolContext(FunctionContext&& function);
		SymbolContext(ParameterContext&& parameter);
		SymbolContext(SymbolContext&&);
		SymbolContext(const SymbolContext&) = delete;
		~SymbolContext();

		SymbolType type() const { return _type; }
		const VariableContext& variable() const { assert(_type == SymbolType::Variable); return _variable; }
		const ParameterContext& parameter() const { assert(_type == SymbolType::Parameter); return _parameter; }
		const FunctionContext& function() const { assert(_type == SymbolType::Function); return _function; }
	};

	using Scope = Table<SymbolContext>;
}

#endif