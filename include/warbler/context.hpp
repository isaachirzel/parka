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
#include <warbler/symbol_table.hpp>

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
	class TypeDefinitionContext;
	class BlockStatementContext;
	class DeclarationContext;

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

	class TypeDefinitionContext;

	class TypeContext
	{
		Array<bool> _ptr_mutability;
		TypeDefinitionContext& _base_type;

	public:

		TypeContext(Array<bool>& ptr_info, TypeDefinitionContext& base_type) :
		_ptr_mutability(std::move(ptr_info)),
		_base_type(base_type)
		{}
	};

	class MemberContext
	{
		TypeContext _type;
		bool _is_public;

	public:

		MemberContext(TypeContext&& type, bool is_public) :
		_type(std::move(type)),
		_is_public(is_public)
		{}
	};

	class StructContext
	{
		Table<MemberContext> _members;

	public:

		StructContext(Table<MemberContext>& members) :
		_members(std::move(members))
		{}
	};

	class PrimitiveContext
	{
	};

	class TypeDefinitionContext
	{
		String _symbol;

		union
		{
			StructContext _struct_def;
		};

		TypeDefinitionType _type;

	public:

		TypeDefinitionContext(String&& symbol, StructContext&& struct_def);
		TypeDefinitionContext(TypeDefinitionContext&& other);
		TypeDefinitionContext(const TypeDefinitionContext& other) = delete;
		~TypeDefinitionContext();


		const auto& symbol() const { return _symbol; }
		const auto& type() const { return _type; }
		const auto& struct_def() const { assert(_type == TypeDefinitionType::Struct); return _struct_def; }
	};

	class VariableContext
	{
		String _name;
		Optional<TypeContext> _type;
		VariableState _state;
		bool _is_mutable;

	public:

		VariableContext(String&& name, TypeContext&& type, bool is_mutable) :
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

		// Context(Assignment::Context&&);
		// Context(Expression::Context&&);
		StatementContext(BlockStatementContext&&);
		StatementContext(DeclarationContext&&);
		// Context(If::Context&&);
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
		TypeContext _return_type;

	public:

		FunctionSignatureContext(Array<ParameterContext>&& parameters, TypeContext&& return_type) :
		_parameters(std::move(parameters)),
		_return_type(std::move(return_type))
		{}
	};

	class ParameterContext
	{
		String _symbol;
		TypeContext _type;
		bool _is_valid;
		bool _is_mutable;


	public:
	
		ParameterContext(String&& symbol, TypeContext&& type, bool is_valid, bool is_mutable) :
		_symbol(std::move(symbol)),
		_type(std::move(type)),
		_is_valid(is_valid),
		_is_mutable(is_mutable)
		{}

		const String& symbol() const { return _symbol; }
	};

	class FunctionContext
	{

		IdentifierContext _name;
		FunctionSignatureContext _signature;
		BlockStatementContext _body;

	public:

		FunctionContext(IdentifierContext&& name, FunctionSignatureContext&& signature, BlockStatementContext&& body) :
		_name(std::move(name)),
		_signature(std::move(signature)),
		_body(std::move(body))
		{}

		const auto& name() const { return _name; }
		const auto& signature() const { return _signature; }
		const auto& body() const { return _body; }
	};

	struct ModuleContext
	{
		String package;
		Table<SymbolContext> symbols;
		Array<FunctionContext> functions;
		Array<TypeDefinitionContext> types;
	};

	struct AstContext
	{
		ModuleContext module;
	};
}

#endif
