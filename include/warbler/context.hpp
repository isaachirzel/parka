#ifndef WARBLER_CONTEXT_HPP
#define WARBLER_CONTEXT_HPP

#include <warbler/type.hpp>
#include <warbler/state.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/table.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/optional.hpp>
#include <warbler/util/box.hpp>

#include <cassert>

namespace warbler
{
	class ConditionalExpressionContext;
	class BooleanOrExpressionContext;
	class BooleanAndExpressionContext;
	class BitwiseOrExpressionContext;
	class BitwiseXorExpressionContext;
	class BitwiseAndExpressionContext;
	class EqualityExpressionContext;
	class RelationalExpressionContext;
	class BitShiftExpressionContext;
	class AdditiveExpressionContext;
	class MultiplicativeExpressionContext;
	class PrefixExpressionContext;
	class PostfixExpressionContext;
	class PrimaryExpressionContext;
	class ConstantContext;
	class VariableContext;
	class ParameterContext;
	class FunctionContext;
	class TypeContext;
	class BlockStatementContext;
	class DeclarationContext;
	class ProgramContext;

	class SymbolContext
	{
		usize _index;
		GlobalSymbolType _type;

	public:

		SymbolContext(GlobalSymbolType type, usize index):
		_index(index),
		_type(type)
		{}

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }
	};

	class IdentifierContext
	{
		String _symbol;

	public:

		IdentifierContext(String && symbol) :
		_symbol(std::move(symbol))
		{}

		const auto& symbol() const { return _symbol; }
	};

	class ExpressionContext
	{
		union
		{
			ConstantContext *_constant;
		};

		ExpressionType _type;

	public:
		
		ExpressionContext(ConstantContext&& constant);
		ExpressionContext(ExpressionContext&& other);
		ExpressionContext(const ExpressionContext&) = delete;
		~ExpressionContext() = default;
	};

	class ConstantContext
	{
		union
		{
			char _character;
			String _string;
			u64 _integer;
			double _floating;
			bool _boolean;
		};

		ConstantType _type;

	public:

		ConstantContext(char character);
		ConstantContext(String&& string);
		ConstantContext(u64 integer);
		ConstantContext(double floating);
		ConstantContext(bool boolean);
		ConstantContext(ConstantContext&&);
		ConstantContext(const ConstantContext&) = delete;
		~ConstantContext();

	};

	class TypeContext;

	class TypeAnnotationContext
	{
		Array<bool> _ptr_mutability;
		usize _index;
		GlobalSymbolType _type;

	public:

		TypeAnnotationContext(Array<bool>&& ptr_info, GlobalSymbolType type, usize index) :
		_ptr_mutability(std::move(ptr_info)),
		_index(index),
		_type(type)
		{}

		const auto& ptr_mutability() const { return _ptr_mutability; }
		const auto& index() const { return _index; }
		const auto& type() const { return _type; }
	};

	struct MemberContext
	{
		String name;
		TypeAnnotationContext type;
		bool is_public;

		MemberContext(String&& name, TypeAnnotationContext&& type, bool is_public) :
		name(std::move(name)),
		type(std::move(type)),
		is_public(is_public)
		{}
	};

	class StructContext
	{
		String _symbol;
		Table<MemberContext> _members;

	public:

		StructContext(String&& symbol, Table<MemberContext>&& members) :
		_symbol(std::move(symbol)),
		_members(std::move(members))
		{}

		const auto& symbol() const { return _symbol; }
		const auto& members() const { return _members; }
	};

	class PrimitiveContext
	{
		const char * _symbol;
		PrimitiveType _type;
		u32 _size;

	public:

		PrimitiveContext(const char *symbol, PrimitiveType type, u32 size):
		_symbol(symbol),
		_type(type),
		_size(size)
		{}

		const char *symbol() const { return _symbol; }
		const auto& type() const { return _type; }
		const auto& size() const { return _size; }
	};

	class TypeContext
	{
		String _symbol;

		union
		{
			StructContext _struct_def;
			PrimitiveContext _primitive;
		};

		TypeDefinitionType _type;

	public:
		
		TypeContext(String&& symbol, StructContext&& struct_def);
		TypeContext(const char *symbol, PrimitiveContext&& primitive);
		TypeContext(TypeContext&& other);
		TypeContext(const TypeContext& other);
		~TypeContext();


		const auto& symbol() const { return _symbol; }
		const auto& type() const { return _type; }
		const auto& struct_def() const { assert(_type == TypeDefinitionType::Struct); return _struct_def; }
	};

	class VariableContext
	{
		String _name;
		Optional<TypeAnnotationContext> _type;
		VariableState _state;
		bool _is_mutable;

	public:

		VariableContext(String&& name, TypeAnnotationContext&& type, bool is_mutable) :
		_name(std::move(name)),
		_type(std::move(type)),
		_is_mutable(is_mutable)
		{}

		const auto& name() const { return _name; }
	};

	class StatementContext
	{
		union
		{
			//Box<AssignmentContext> _assignment;
			//Box<ExpressionStatementContext> _expression;
			Box<BlockStatementContext> _block;
			Box<DeclarationContext> _declaration;
			// If::Context *_if;
		};

		StatementType _type;

	public:

		StatementContext(BlockStatementContext&&);
		StatementContext(DeclarationContext&&);
		StatementContext(StatementContext&&);
		StatementContext(const StatementContext&) = delete;
		~StatementContext();
	};

	class ExpressionStatementContext
	{
	};

	class DeclarationContext
	{
		VariableContext _variable;
		ExpressionContext _value;

	public:

	};

	class AssignmentContext
	{
	};

	class BlockStatementContext
	{
		Array<Box<StatementContext>> _statements;

	public:

		BlockStatementContext(Array<Box<StatementContext>>&& statements) :
		_statements(std::move(statements))
		{}
	};

	class FunctionSignatureContext
	{
		Array<ParameterContext> _parameters;
		Optional<TypeAnnotationContext> _return_type;

	public:

		FunctionSignatureContext(Array<ParameterContext>&& parameters, Optional<TypeAnnotationContext>&& return_type) :
		_parameters(std::move(parameters)),
		_return_type(std::move(return_type))
		{}
	};

	class ParameterContext
	{
		String _symbol;
		TypeAnnotationContext _type;
		bool _is_valid;
		bool _is_mutable;


	public:
	
		ParameterContext(String&& symbol, TypeAnnotationContext&& type, bool is_valid, bool is_mutable) :
		_symbol(std::move(symbol)),
		_type(std::move(type)),
		_is_valid(is_valid),
		_is_mutable(is_mutable)
		{}

		const String& symbol() const { return _symbol; }
	};

	class FunctionContext
	{

		String _symbol;
		FunctionSignatureContext _signature;
		BlockStatementContext _body;

	public:

		FunctionContext(String&& symbol, FunctionSignatureContext&& signature, BlockStatementContext&& body) :
		_symbol(std::move(symbol)),
		_signature(std::move(signature)),
		_body(std::move(body))
		{}

		const auto& name() const { return _symbol; }
		const auto& signature() const { return _signature; }
		const auto& body() const { return _body; }
	};

	struct PackageContext
	{
		String name;
	};

	class ProgramContext
	{
		Array<StructContext> _structs;
		Array<PrimitiveContext> _primitives;

	public:

		ProgramContext(Array<StructContext>&& structs, Array<PrimitiveContext>&& primitives):
		_structs(std::move(structs)),
		_primitives(std::move(primitives))
		{}

		const auto& structs() const { return _structs; }
		const auto& primitives() const { return _primitives; }
	};
}

#endif
