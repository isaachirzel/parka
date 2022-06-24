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
	enum PrimitiveIndex
	{
		UINT_LITERAL_INDEX,
		U8_INDEX,
		U16_INDEX,
		U32_INDEX,
		U64_INDEX,
		INT_LITERAL_INDEX,
		I8_INDEX,
		I16_INDEX,
		I32_INDEX,
		I64_INDEX,
		FLOAT_LITERAL_INDEX,
		F32_INDEX,
		F64_INDEX,
		BOOL_INDEX,
		CHAR_INDEX
	};

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
	class ExpressionStatementContext;
	class BlockStatementContext;
	class DeclarationContext;

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

	class TypeAnnotationContext
	{
		Array<bool> _ptr_mutability;
		usize _index;
		AnnotationType _type;

	public:

		TypeAnnotationContext(usize index):
		_index(index),
		_type(AnnotationType::Primitive)
		{}

		TypeAnnotationContext(Array<bool>&& ptr_info, AnnotationType type, usize index) :
		_ptr_mutability(std::move(ptr_info)),
		_index(index),
		_type(type)
		{}

		const auto& ptr_mutability() const { return _ptr_mutability; }
		const auto& index() const { return _index; }
		const auto& type() const { return _type; }
	};

	class ExpressionContext
	{
		union
		{
			Box<ConstantContext> _constant;
		};

		ExpressionType _type;

	public:
		
		ExpressionContext(ConstantContext&& constant);
		ExpressionContext(ExpressionContext&& other);
		ExpressionContext(const ExpressionContext&) = delete;
		~ExpressionContext();

		const auto& type() const { return _type; }
		const auto& constant() const { assert(_type == ExpressionType::Constant); return *_constant; }
		TypeAnnotationContext type_annotation() const;
	};

	class ConstantContext
	{
		union
		{
			char _character;
			String _string;
			i64 _integer;
			u64 _uinteger;
			double _floating;
			bool _boolean;
		};

		ConstantType _type;

	public:

		ConstantContext(char character);
		ConstantContext(const String& string);
		ConstantContext(i64 integer);
		ConstantContext(u64 uinteger);
		ConstantContext(double floating);
		ConstantContext(bool boolean);
		ConstantContext(ConstantContext&&);
		ConstantContext(const ConstantContext&) = delete;
		~ConstantContext();

		const auto& type() const { return _type; }
		const auto& character() const { return _character; }
		const auto& string() const { return _string; }
		const auto& integer() const { return _integer; }
		const auto& uinteger() const { return _uinteger; }
		const auto& floating() const { return _floating; }
		const auto& boolean() const { return _boolean; }
		TypeAnnotationContext type_annotation() const;
		usize index() const;
	};

	struct MemberContext
	{
		String _name;
		TypeAnnotationContext _type;
		bool _is_public;

	public:

		MemberContext(String&& name, TypeAnnotationContext&& type, bool is_public) :
		_name(std::move(name)),
		_type(std::move(type)),
		_is_public(is_public)
		{}

		const auto& name() const { return _name; }
		const auto& type() const { return _type; }
		const auto& is_public() const { return _is_public; }
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
		PrimitiveType _type;
		u32 _size;

	public:

		PrimitiveContext(PrimitiveType type, usize size = 0):
		_type(type),
		_size(size)
		{}

		const auto& type() const { return _type; }
		const auto& size() const { return _size; }
		const char *type_name() const;
		bool is_literal() const { return _size == 0; }
	};

	class VariableContext
	{
		String _name;
		Optional<TypeAnnotationContext> _type;
		bool _is_mutable;

	public:

		VariableContext(String&& name, bool is_mutable):
		_name(std::move(name)),
		_type(),
		_is_mutable(is_mutable)
		{}

		VariableContext(String&& name, Optional<TypeAnnotationContext>&& type, bool is_mutable) :
		_name(std::move(name)),
		_type(std::move(type)),
		_is_mutable(is_mutable)
		{}

		const auto& name() const { return _name; }
		bool is_auto_type() const { return !_type.has_value(); }
		const auto& type() const { assert(_type.has_value()); return *_type; }
	};

	class StatementContext
	{
		union
		{
			Box<ExpressionStatementContext> _expression;
			Box<BlockStatementContext> _block;
			Box<DeclarationContext> _declaration;
		};

		StatementType _type;

	public:

		StatementContext(BlockStatementContext&& );
		StatementContext(DeclarationContext&&);
		StatementContext(ExpressionStatementContext&&);
		StatementContext(StatementContext&&);
		StatementContext(const StatementContext&) = delete;
		~StatementContext();

		const auto& type() const { return _type; }
		const auto& block() const { assert(_type == StatementType::Block); return *_block; }
		const auto& expression() const { assert(_type == StatementType::Expression); return *_expression; }
		const auto& declaration() const { assert(_type == StatementType::Declaration); return *_declaration; }
	};

	class DeclarationContext
	{
		VariableContext _variable;
		ExpressionContext _value;

	public:

		DeclarationContext(VariableContext&& variable, ExpressionContext&& value):
		_variable(std::move(variable)),
		_value(std::move(value))
		{}

		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};

	class ExpressionStatementContext
	{
		ExpressionContext _expression;

	public:

		ExpressionStatementContext(ExpressionContext&& expression):
		_expression(std::move(expression))
		{}

		const auto& expression() const { return _expression; }
	};

	class BlockStatementContext
	{
		Array<StatementContext> _statements;

	public:

		BlockStatementContext(Array<StatementContext>&& statements) :
		_statements(std::move(statements))
		{}

		const auto& statements() const { return _statements; }
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

		const auto& parameters() const { return _parameters; }
		const auto& return_type() const { return _return_type; }		
	};

	class ParameterContext
	{
		String _name;
		TypeAnnotationContext _type;
		bool _is_mutable;


	public:
	
		ParameterContext(String&& name, TypeAnnotationContext&& type, bool is_mutable) :
		_name(std::move(name)),
		_type(std::move(type)),
		_is_mutable(is_mutable)
		{}

		const auto& name() const { return _name; }
		const auto& type() const { return _type; }
		const auto& is_mutable() const { return _is_mutable; }
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
		Array<FunctionContext> _functions;

	public:

		ProgramContext(Array<StructContext>&& structs, Array<FunctionContext>&& functions):
		_structs(std::move(structs)),
		_functions(std::move(functions))
		{}

		const auto& structs() const { return _structs; }
		const auto& functions() const { return _functions; }
	};

	extern PrimitiveContext primitives[];
	extern usize primitive_count;
}

#endif
