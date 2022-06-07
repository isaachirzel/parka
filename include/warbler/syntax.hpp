#ifndef WARBLER_SYNTAX_HPP
#define WARBLER_SYNTAX_HPP

#include <warbler/token.hpp>
#include <warbler/type.hpp>
#include <warbler/util/optional.hpp>
#include <warbler/util/box.hpp>
#include <warbler/util/table.hpp>

namespace warbler
{
	class ConditionalExpressionSyntax;
	class BooleanOrExpressionSyntax;
	class BooleanAndExpressionSyntax;
	class BitwiseOrExpressionSyntax;
	class BitwiseXorExpressionSyntax;
	class BitwiseAndExpressionSyntax;
	class EqualityExpressionSyntax;
	class RelationalExpressionSyntax;
	class BitShiftExpressionSyntax;
	class AdditiveExpressionSyntax;
	class MultiplicativeExpressionSyntax;
	class PrefixExpressionSyntax;
	class PostfixExpressionSyntax;
	class PrimaryExpressionSyntax;
	class ConstantSyntax;
	class SymbolSyntax;
	class AssignmentSyntax;
	class ExpressionStatementSyntax;
	class BlockStatementSyntax;
	class DeclarationSyntax;
	class IfStatementSyntax;

	class SymbolSyntax
	{
		Token _token;

	public:

		SymbolSyntax(const Token& token) :
		_token(token)
		{}
	};

	class LabelSyntax
	{
		Token _token;

	public:

		LabelSyntax(const Token& token) :
		_token(token)
		{}
	};

	class ExpressionSyntax
	{
		union
		{
			ConditionalExpressionSyntax *_conditional;
			BooleanOrExpressionSyntax *_boolean_or;
			BooleanAndExpressionSyntax *_boolean_and;
			BitwiseOrExpressionSyntax *_bitwise_or;
			BitwiseXorExpressionSyntax *_bitwise_xor;
			BitwiseAndExpressionSyntax *_bitwise_and;
			EqualityExpressionSyntax *_equality;
			RelationalExpressionSyntax *_relational;
			BitShiftExpressionSyntax *_shift;
			AdditiveExpressionSyntax *_additive;
			MultiplicativeExpressionSyntax *_multiplicative;
			PrefixExpressionSyntax *_prefix;
			PostfixExpressionSyntax *_postfix;
			PrimaryExpressionSyntax *_primary;
			ConstantSyntax *_constant;
			SymbolSyntax *_symbol;
		};

		ExpressionType _type;
	
	public:

		ExpressionSyntax(ConditionalExpressionSyntax&&);
		ExpressionSyntax(BooleanOrExpressionSyntax&&);
		ExpressionSyntax(BooleanAndExpressionSyntax&&);
		ExpressionSyntax(BitwiseOrExpressionSyntax&&);
		ExpressionSyntax(BitwiseXorExpressionSyntax&&);
		ExpressionSyntax(BitwiseAndExpressionSyntax&&);
		ExpressionSyntax(EqualityExpressionSyntax&&);
		ExpressionSyntax(RelationalExpressionSyntax&&);
		ExpressionSyntax(BitShiftExpressionSyntax&&);
		ExpressionSyntax(AdditiveExpressionSyntax&&);
		ExpressionSyntax(MultiplicativeExpressionSyntax&&);
		ExpressionSyntax(PrefixExpressionSyntax&&);
		ExpressionSyntax(PostfixExpressionSyntax&&);
		ExpressionSyntax(PrimaryExpressionSyntax&&);
		ExpressionSyntax(ConstantSyntax&&);
		ExpressionSyntax(SymbolSyntax&&);
		ExpressionSyntax(ExpressionSyntax&&);
		ExpressionSyntax& operator=(ExpressionSyntax&&) = default;
		ExpressionSyntax(const ExpressionSyntax&) = delete;
		ExpressionSyntax& operator=(const ExpressionSyntax&) = delete;
		~ExpressionSyntax();

		ExpressionType type() const { return _type; }
		const ConditionalExpressionSyntax& conditional() const { assert(_type == ExpressionType::conditional); return *_conditional; }
		const BooleanOrExpressionSyntax& boolean_or() const { assert(_type == ExpressionType::BooleanOr); return *_boolean_or; }
		const BooleanAndExpressionSyntax& boolean_and() const { assert(_type == ExpressionType::BooleanAnd); return *_boolean_and; }
		const BitwiseOrExpressionSyntax& bitwise_or() const { assert(_type == ExpressionType::BitwiseOr); return *_bitwise_or; }
		const BitwiseXorExpressionSyntax& bitwise_xor() const { assert(_type == ExpressionType::BitwiseXor); return *_bitwise_xor; }
		const BitwiseAndExpressionSyntax& bitwise_and() const { assert(_type == ExpressionType::BitwiseAnd); return *_bitwise_and; }
		const EqualityExpressionSyntax& equality() const { assert(_type == ExpressionType::Equality); return *_equality; }
		const RelationalExpressionSyntax& relational() const { assert(_type == ExpressionType::Relational); return *_relational; }
		const BitShiftExpressionSyntax& bit_shift() const { assert(_type == ExpressionType::Shift); return *_shift; }
		const AdditiveExpressionSyntax& additive() const { assert(_type == ExpressionType::Additive); return *_additive; }
		const MultiplicativeExpressionSyntax& multiplicative() const { assert(_type == ExpressionType::Multiplicative); return *_multiplicative; }
		const PrefixExpressionSyntax& prefix() const { assert(_type == ExpressionType::Prefix); return *_prefix; }
		const PostfixExpressionSyntax& postfix() const { assert(_type == ExpressionType::Postfix); return *_postfix; }
		const PrimaryExpressionSyntax& primary() const { assert(_type == ExpressionType::Primary); return *_primary; }
		const ConstantSyntax& constant() const { assert(_type == ExpressionType::Constant); return *_constant; }
		const SymbolSyntax& symbol() const { assert(_type == ExpressionType::Symbol); return *_symbol; }
	};

	class ConstantSyntax
	{
	private:

		Token _token;

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

		ConstantSyntax(const Token& token, String&& string);
		ConstantSyntax(const Token& token, char character);
		ConstantSyntax(const Token& token, u64 integer);
		ConstantSyntax(const Token& token, double floating);
		ConstantSyntax(const Token& token, bool boolean);
		ConstantSyntax(ConstantSyntax&&);
		ConstantSyntax(const ConstantSyntax&) = delete;
		~ConstantSyntax();

		const Token& token() const { return _token; }
		const auto& character() const { return _character; }
		const auto& string() const { return _string; }
		const auto& integer() const { return _integer; }
		const auto& floating() const { return _floating; }
		const auto& boolean() const { return _boolean; }
		const auto& type() const { return _type; }

		ConstantSyntax& operator=(ConstantSyntax&& other);
		ConstantSyntax& operator=(const ConstantSyntax& other) = delete;
	};

	class PrimaryExpressionSyntax
	{
	};

	class PostfixExpressionSyntax
	{
	private:

		ExpressionSyntax _expression;

		union
		{
			ExpressionSyntax _index;
			Array<ExpressionSyntax> _arguments;
			Token _member;
		};

		PostfixType _type;

	public:

		PostfixExpressionSyntax(ExpressionSyntax&& expression, ExpressionSyntax&& index);
		PostfixExpressionSyntax(ExpressionSyntax&& expression, Array<ExpressionSyntax>&& arguments);
		PostfixExpressionSyntax(ExpressionSyntax&& expression, const Token& member);
		PostfixExpressionSyntax(PostfixExpressionSyntax&& other);
		PostfixExpressionSyntax(const PostfixExpressionSyntax& other) = delete;
		~PostfixExpressionSyntax();
	};

	class PrefixExpressionSyntax
	{
	private:

		Token _token;
		ExpressionSyntax _expression;
		PrefixType _type;

	public:

		PrefixExpressionSyntax(const Token& token, ExpressionSyntax&& expression, PrefixType type) :
		_token(token),
		_expression(std::move(expression)),
		_type(type)
		{}
	};

	struct MultiplicativeRhsSyntax
	{
		ExpressionSyntax expr;
		MultiplicativeType type;
	};

	class MultiplicativeExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<MultiplicativeRhsSyntax> _RhsSyntax;
	
	public:

		MultiplicativeExpressionSyntax(ExpressionSyntax&& lhs, Array<MultiplicativeRhsSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	struct AdditiveRhsSyntax
	{
		ExpressionSyntax expr;
		AdditiveType type;
	};

	class AdditiveExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<AdditiveRhsSyntax> _RhsSyntax;
	
	public:

		AdditiveExpressionSyntax(ExpressionSyntax&& lhs, Array<AdditiveRhsSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	struct BitShiftRhsSyntax
	{
		ExpressionSyntax expr;
		BitShiftType type;
	};

	class BitShiftExpressionSyntax
	{
		ExpressionSyntax _lhs;
		Array<BitShiftRhsSyntax> _RhsSyntax;

	public:

		BitShiftExpressionSyntax(ExpressionSyntax&& lhs, Array<BitShiftRhsSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	struct RelationalRhsSyntax
	{
		ExpressionSyntax expr;
		RelationalType type;
	};

	class RelationalExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<RelationalRhsSyntax> _RhsSyntax;

	public:

		RelationalExpressionSyntax(ExpressionSyntax&& lhs, Array<RelationalRhsSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	struct EqualityRhsSyntax
	{
		ExpressionSyntax expr;
		EqualityType type;
	};

	class EqualityExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<EqualityRhsSyntax> _RhsSyntax;

	public:

		EqualityExpressionSyntax(ExpressionSyntax&& lhs, Array<EqualityRhsSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	class BitwiseAndExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<ExpressionSyntax> _RhsSyntax;

	public:

		BitwiseAndExpressionSyntax(ExpressionSyntax&& lhs, Array<ExpressionSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	class BitwiseXorExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<ExpressionSyntax> _RhsSyntax;

	public:

		BitwiseXorExpressionSyntax(ExpressionSyntax&& lhs, Array<ExpressionSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	class BitwiseOrExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<ExpressionSyntax> _RhsSyntax;	

	public:

		BitwiseOrExpressionSyntax(ExpressionSyntax&& lhs, Array<ExpressionSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	class BooleanAndExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<ExpressionSyntax> _RhsSyntax;

	public:

		BooleanAndExpressionSyntax(ExpressionSyntax&& lhs, Array<ExpressionSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	class BooleanOrExpressionSyntax
	{
	private:

		ExpressionSyntax _lhs;
		Array<ExpressionSyntax> _RhsSyntax;

	public:

		BooleanOrExpressionSyntax(ExpressionSyntax&& lhs, Array<ExpressionSyntax>&& RhsSyntax) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax))
		{}
	};

	struct ConditionalRhsSyntax
	{
		ExpressionSyntax _true_case;
		ExpressionSyntax _false_case;

		ConditionalRhsSyntax(ExpressionSyntax&& true_case, ExpressionSyntax&& false_case) :
		_true_case(std::move(true_case)),
		_false_case(std::move(false_case))
		{}
	};

	class ConditionalExpressionSyntax
	{
	private: // members

		ExpressionSyntax _lhs;
		Optional<ConditionalRhsSyntax> _RhsSyntax;

	public: // methods

		ConditionalExpressionSyntax(ExpressionSyntax&& lhs) :
		_lhs(std::move(lhs)),
		_RhsSyntax()
		{}

		ConditionalExpressionSyntax(ExpressionSyntax&& lhs, ExpressionSyntax&& true_case, ExpressionSyntax&& false_case) :
		_lhs(std::move(lhs)),
		_RhsSyntax(Optional<ConditionalRhsSyntax>(ConditionalRhsSyntax { std::move(true_case), std::move(false_case) }))
		{}
	};

	struct PtrSyntax
	{
		Token token;
		bool is_mutable;
	};

	class TypeAnnotationSyntax
	{
		Token _name;
		Array<PtrSyntax> _ptrs;

	public:

		TypeAnnotationSyntax(const Token& name, Array<PtrSyntax>&& ptrs) :
		_name(name),
		_ptrs(std::move(ptrs))
		{}

		const auto& name() const { return _name; }
		const auto& ptrs() const { return _ptrs; }
	};

	class MemberSyntax
	{
		Token _name;
		TypeAnnotationSyntax _type;
		bool _is_public;

	public:

		MemberSyntax(const Token& name, TypeAnnotationSyntax&& type, bool is_public) :
		_name(name),
		_type(std::move(type)),
		_is_public(is_public)
		{}

		const auto& name() const { return _name; }
		const auto& type() const { return _type; }
		const auto& is_public() const { return _is_public; }
	};

	class EnumSyntax
	{
		Array<MemberSyntax> _values;

	public:

		EnumSyntax(Array<MemberSyntax>&& values) :
		_values(std::move(values))
		{}
	};

	class StructSyntax
	{
		Token _name;
		Array<MemberSyntax> _members;

	public:

		StructSyntax(const Token& name, Array<MemberSyntax>& members) :
		_name(name),
		_members(std::move(members))
		{}

		const auto& name() const { return _name; }
		const auto& members() const { return _members; }
	};

	class TypeSyntax
	{
		Token _name;
		
		union
		{
			StructSyntax _struct;
		};
		
		TypeDefinitionType _type;

	public:

		TypeSyntax(const Token& name, StructSyntax&& struct_def);
		TypeSyntax(TypeSyntax&& other);
		TypeSyntax(const TypeSyntax& other) = delete;
		~TypeSyntax();


		const auto& name() const { return _name; }
		const auto& type() const { return _type; }
		const auto& struct_syntax() const { assert(_type == TypeDefinitionType::Struct); return _struct; }
	};

	class VariableSyntax
	{
	private:

		Token _name;
		Optional<TypeAnnotationSyntax> _type;
		bool _is_mutable;

	public:

		VariableSyntax(const Token& name, bool is_mutable):
		_name(name),
		_type(),
		_is_mutable(is_mutable)
		{}

		VariableSyntax(const Token& name, TypeAnnotationSyntax&& type, bool is_mutable) :
		_name(name),
		_type(std::move(type)),
		_is_mutable(is_mutable)
		{}

		bool is_mutable() const { return _is_mutable; }
		bool is_auto_type() const { return !_type.has_value(); }

		const auto& name() const { return _name; }
		const auto& type() const { assert(_type.has_value()); return *_type; }
	};

	class StatementSyntax
	{
		union
		{
			AssignmentSyntax *_assignment;
			ExpressionStatementSyntax *_expression;
			BlockStatementSyntax *_block;
			DeclarationSyntax *_declaration;
			IfStatementSyntax *_iff;
		};

		StatementType _type;

	public:

		StatementSyntax(AssignmentSyntax&&);
		StatementSyntax(ExpressionStatementSyntax&&);
		StatementSyntax(BlockStatementSyntax&&);
		StatementSyntax(DeclarationSyntax&&);
		StatementSyntax(IfStatementSyntax&&);
		StatementSyntax(StatementSyntax&&);
		StatementSyntax(const StatementSyntax&) = delete;
		~StatementSyntax();
		
		const auto& type() const { return _type; }
		const auto& declaration() const { assert(_type == StatementType::Declaration); return *_declaration; }
		const auto& block() const { assert(_type == StatementType::Block); return *_block; }
	};

	class BlockStatementSyntax
	{
		Array<StatementSyntax> _statements;

	public:

		BlockStatementSyntax(Array<StatementSyntax>&& statements) :
		_statements(std::move(statements))
		{}

		const auto& statements() const { return _statements; }
	};

	class JumpStatementSyntax
	{
		ExpressionSyntax *_value;
		JumpType _type;

	public:

		JumpStatementSyntax(ExpressionSyntax *value, JumpType type);
	};

	class IfStatementSyntax
	{
	private:

		ExpressionSyntax _condition;
		BlockStatementSyntax _then_body;

		union
		{
			BlockStatementSyntax _else_body;
			IfStatementSyntax *_else_if;
		};

		IfType _type;

	public:

		IfStatementSyntax(ExpressionSyntax&& condition, BlockStatementSyntax&& then_body);
		IfStatementSyntax(ExpressionSyntax&& condition, BlockStatementSyntax&& then_body, BlockStatementSyntax&& else_body);
		IfStatementSyntax(ExpressionSyntax&& condition, BlockStatementSyntax&& then_body, IfStatementSyntax *else_if);
		IfStatementSyntax(IfStatementSyntax&& other);
		IfStatementSyntax(const IfStatementSyntax& other) = delete;
		~IfStatementSyntax();
	};

	class ExpressionStatementSyntax
	{
	private:

		ExpressionSyntax _expression;

	public:

		ExpressionStatementSyntax(ExpressionSyntax&& expression) :
		_expression(std::move(expression))
		{}
	};

	class DeclarationSyntax
	{
		VariableSyntax _variable;
		ExpressionSyntax _value;

	public:

		DeclarationSyntax(VariableSyntax&& variable, ExpressionSyntax&& value) :
		_variable(std::move(variable)),
		_value(std::move(value))
		{}

		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};

	class AssignmentSyntax
	{
	private:

		ExpressionSyntax _lhs;
		ExpressionSyntax _RhsSyntax;
		AssignmentType _type;

	public:

		AssignmentSyntax(ExpressionSyntax&& lhs, ExpressionSyntax &&RhsSyntax, AssignmentType type) :
		_lhs(std::move(lhs)),
		_RhsSyntax(std::move(RhsSyntax)),
		_type(type)
		{}
	};

	class LoopStatementSyntax
	{
		Array<StatementSyntax> _body;
		//LoopCondition _condition;
		LoopType _type;

	public:

		LoopStatementSyntax(Array<StatementSyntax>&& body, LoopType type);
	};

	class ParameterSyntax
	{
		Token _name;
		TypeAnnotationSyntax _type;
		bool _is_mutable;

	public:

		ParameterSyntax(const Token& name, TypeAnnotationSyntax&& type, bool is_mutable) :
		_name(name),
		_type(std::move(type)),
		_is_mutable(is_mutable)
		{}

		const auto& name() const { return _name; }
		const auto& type() const { return _type; }
		const auto& is_mutable() const { return _is_mutable; }
	};

	class FunctionSignatureSyntax
	{
		Array<ParameterSyntax> _parameters;
		Optional<TypeAnnotationSyntax> _return_type;
	
	public:

		FunctionSignatureSyntax(Array<ParameterSyntax>&& parameters):
		_parameters(std::move(parameters)),
		_return_type()
		{}

		FunctionSignatureSyntax(Array<ParameterSyntax>&& parameters, TypeAnnotationSyntax&& return_type) :
		_parameters(std::move(parameters)),
		_return_type(std::move(return_type))
		{}

		const auto& parameters() const { return _parameters; }
		const auto& return_type() const { return _return_type; }
	};

	class FunctionSyntax
	{
		Token _name;		
		FunctionSignatureSyntax _signature;
		BlockStatementSyntax _body;

	public:

		FunctionSyntax(const Token& name, FunctionSignatureSyntax&& signature, BlockStatementSyntax&& body) :
		_name(name),
		_signature(std::move(signature)),
		_body(std::move(body))
		{}

		const auto& name() const { return _name; }
		const auto& signature() const { return _signature; }
		const auto& body() const { return _body; }
	};
	
	struct ModuleSyntax
	{
		Array<FunctionSyntax> functions;
		Array<StructSyntax> structs;
	};

	class PackageSyntax
	{
		String _name;
		Array<FunctionSyntax> _functions;
		Array<StructSyntax> _structs;
		// TODO: add globals

	public:

		PackageSyntax(const String& name, Array<FunctionSyntax>&& functions, Array<StructSyntax>&& structs) :
		_name(name),
		_functions(std::move(functions)),
		_structs(std::move(structs))
		{}
		
		const auto& name() const { return _name; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }
	};

	class ProgramSyntax
	{
		Array<PackageSyntax> _packages;

	public:

		ProgramSyntax(Array<PackageSyntax>&& packages) :
		_packages(std::move(packages))
		{}

		const auto& packages() const { return _packages; }
	};
}

/*
Array of symbols with pointers to syntax
Table of 



Current Location		Looking for
a::b::c					b2::Doggy

a::b::c::b2::Doggy	No
a::b::b2::Doggy		No
a::b2::Doggy		Yes
*/

#endif
