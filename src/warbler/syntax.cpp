#include <warbler/syntax.hpp>

namespace warbler
{
	ConstantSyntax::ConstantSyntax(const Token& token, char character) :
	_token(token),
	_character(character),
	_type(ConstantType::Character)
	{}

	ConstantSyntax::ConstantSyntax(const Token& token, String&& string) :
	_token(token),
	_string(std::move(string)),
	_type(ConstantType::String)
	{}

	ConstantSyntax::ConstantSyntax(const Token& token, u64 integer) :
	_token(token),
	_integer(integer),
	_type(ConstantType::Integer)
	{}

	ConstantSyntax::ConstantSyntax(const Token& token, double floating) :
	_token(token),
	_floating(floating),
	_type(ConstantType::Float)
	{}

	ConstantSyntax::ConstantSyntax(const Token& token, bool boolean) :
	_token(token),
	_boolean(boolean),
	_type(ConstantType::Boolean)
	{}

	ConstantSyntax::ConstantSyntax(ConstantSyntax&& other) :
	_token(other._token),
	_type(other._type)
	{
		switch (_type)
		{
			case ConstantType::Character:
				_character = other._character;
				break;

			case ConstantType::String:
				new(&_string) auto(std::move(other._string));
				break;

			case ConstantType::Integer:
				_integer = other._integer;
				break;

			case ConstantType::Float:
				_floating = other._floating;
				break;

			case ConstantType::Boolean:
				_boolean = other._boolean;
				break;
		}
	}

	ConstantSyntax::~ConstantSyntax()
	{
		if (_type == ConstantType::String)
			_string.~basic_string();
	}

	ExpressionSyntax::ExpressionSyntax(ConditionalExpressionSyntax&& conditional) :
	_conditional(new ConditionalExpressionSyntax(std::move(conditional))),
	_type(ExpressionType::conditional)
	{}

	ExpressionSyntax::ExpressionSyntax(BooleanOrExpressionSyntax&& boolean_or) :
	_boolean_or(new BooleanOrExpressionSyntax(std::move(boolean_or))),
	_type(ExpressionType::BooleanOr)
	{}

	ExpressionSyntax::ExpressionSyntax(BooleanAndExpressionSyntax&& boolean_and) :
	_boolean_and(new BooleanAndExpressionSyntax(std::move(boolean_and))),
	_type(ExpressionType::BooleanAnd)
	{}

	ExpressionSyntax::ExpressionSyntax(BitwiseOrExpressionSyntax&& bitwise_or) :
	_bitwise_or(new BitwiseOrExpressionSyntax(std::move(bitwise_or))),
	_type(ExpressionType::BitwiseOr)
	{}

	ExpressionSyntax::ExpressionSyntax(BitwiseXorExpressionSyntax&& bitwise_xor) :
	_bitwise_xor(new BitwiseXorExpressionSyntax(std::move(bitwise_xor))),
	_type(ExpressionType::BitwiseXor)
	{}

	ExpressionSyntax::ExpressionSyntax(BitwiseAndExpressionSyntax&& bitwise_and) :
	_bitwise_and(new BitwiseAndExpressionSyntax(std::move(bitwise_and))),
	_type(ExpressionType::BitwiseAnd)
	{}

	ExpressionSyntax::ExpressionSyntax(EqualityExpressionSyntax&& equality) :
	_equality(new EqualityExpressionSyntax(std::move(equality))),
	_type(ExpressionType::Equality)
	{}

	ExpressionSyntax::ExpressionSyntax(RelationalExpressionSyntax&& relational) :
	_relational(new RelationalExpressionSyntax(std::move(relational))),
	_type(ExpressionType::Relational)
	{}

	ExpressionSyntax::ExpressionSyntax(BitShiftExpressionSyntax&& shift) :
	_shift(new BitShiftExpressionSyntax(std::move(shift))),
	_type(ExpressionType::Shift)
	{}

	ExpressionSyntax::ExpressionSyntax(AdditiveExpressionSyntax&& additive) :
	_additive(new AdditiveExpressionSyntax(std::move(additive))),
	_type(ExpressionType::Additive)
	{}

	ExpressionSyntax::ExpressionSyntax(MultiplicativeExpressionSyntax&& multiplicative) :
	_multiplicative(new MultiplicativeExpressionSyntax(std::move(multiplicative))),
	_type(ExpressionType::Multiplicative)
	{}

	ExpressionSyntax::ExpressionSyntax(PrefixExpressionSyntax&& prefix) :
	_prefix(new PrefixExpressionSyntax(std::move(prefix))),
	_type(ExpressionType::Prefix)
	{}

	ExpressionSyntax::ExpressionSyntax(PostfixExpressionSyntax&& postfix) :
	_postfix(new PostfixExpressionSyntax(std::move(postfix))),
	_type(ExpressionType::Postfix)
	{}

	ExpressionSyntax::ExpressionSyntax(PrimaryExpressionSyntax&& primary) :
	_primary(new PrimaryExpressionSyntax(std::move(primary))),
	_type(ExpressionType::Primary)
	{}

	ExpressionSyntax::ExpressionSyntax(ConstantSyntax&& constant) :
	_constant(new ConstantSyntax(std::move(constant))),
	_type(ExpressionType::Constant)
	{}

	ExpressionSyntax::ExpressionSyntax(SymbolSyntax&& symbol) :
	_symbol(new SymbolSyntax(std::move(symbol))),
	_type(ExpressionType::Symbol)
	{}

	ExpressionSyntax::ExpressionSyntax(ExpressionSyntax&& other) :
	_type(other._type)
	{
		switch (_type)
		{
		case ExpressionType::conditional:
			_conditional = other._conditional;
			other._conditional = nullptr;
			break;
		case ExpressionType::BooleanOr:
			_boolean_or = other._boolean_or;
			other._boolean_or = nullptr;
			break;
		case ExpressionType::BooleanAnd:
			_boolean_and = other._boolean_and;
			other._boolean_and = nullptr;
			break;
		case ExpressionType::BitwiseOr:
			_bitwise_or = other._bitwise_or;
			other._bitwise_or = nullptr;
			break;
		case ExpressionType::BitwiseXor:
			_bitwise_xor = other._bitwise_xor;
			other._bitwise_xor = nullptr;
			break;
		case ExpressionType::BitwiseAnd:
			_bitwise_and = other._bitwise_and;
			other._bitwise_and = nullptr;
			break;
		case ExpressionType::Equality:
			_equality = other._equality;
			other._equality = nullptr;
			break;
		case ExpressionType::Relational:
			_relational = other._relational;
			other._relational = nullptr;
			break;
		case ExpressionType::Shift:
			_shift = other._shift;
			other._shift = nullptr;
			break;
		case ExpressionType::Additive:
			_additive = other._additive;
			other._additive = nullptr;
			break;
		case ExpressionType::Multiplicative:
			_multiplicative = other._multiplicative;
			other._multiplicative = nullptr;
			break;
		case ExpressionType::Postfix:
			_prefix = other._prefix;
			other._prefix = nullptr;
			break;
		case ExpressionType::Prefix:
			_postfix = other._postfix;
			other._postfix = nullptr;
			break;
		case ExpressionType::Primary:
			_primary = other._primary;
			other._primary = nullptr;
			break;
		case ExpressionType::Constant:
			_constant = other._constant;
			other._constant = nullptr;
			break;
		case ExpressionType::Symbol:
			_symbol = other._symbol;
			other._symbol = nullptr;
			break;
		}
	}

	ExpressionSyntax::~ExpressionSyntax()
	{
		switch (_type)
		{
		case ExpressionType::conditional:
			delete _conditional;
			break;
		case ExpressionType::BooleanOr:
			delete _boolean_or;
			break;
		case ExpressionType::BooleanAnd:
			delete _boolean_and;
			break;
		case ExpressionType::BitwiseOr:
			delete _bitwise_or;
			break;
		case ExpressionType::BitwiseXor:
			delete _bitwise_xor;
			break;
		case ExpressionType::BitwiseAnd:
			delete _bitwise_and;
			break;
		case ExpressionType::Equality:
			delete _equality;
			break;
		case ExpressionType::Relational:
			delete _relational;
			break;
		case ExpressionType::Shift:
			delete _shift;
			break;
		case ExpressionType::Additive:
			delete _additive;
			break;
		case ExpressionType::Multiplicative:
			delete _multiplicative;
			break;
		case ExpressionType::Postfix:
			delete _prefix;
			break;
		case ExpressionType::Prefix:
			delete _postfix;
			break;
		case ExpressionType::Primary:
			delete _primary;
			break;
		case ExpressionType::Constant:
			delete _constant;
			break;
		case ExpressionType::Symbol:
			delete _symbol;
			break;
		}
	}

	PostfixExpressionSyntax::PostfixExpressionSyntax(ExpressionSyntax&& expression, ExpressionSyntax&& index) :
	_expression(std::move(expression)),
	_index(std::move(index)),
	_type(PostfixType::Index)
	{}

	PostfixExpressionSyntax::PostfixExpressionSyntax(ExpressionSyntax&& expression, Array<ExpressionSyntax>&& arguments) :
	_expression(std::move(expression)),
	_arguments(std::move(arguments)),
	_type(PostfixType::FunctionCall)
	{}

	PostfixExpressionSyntax::PostfixExpressionSyntax(ExpressionSyntax&& expression, IdentifierSyntax&& member) :
	_expression(std::move(expression)),
	_member(std::move(member)),
	_type(PostfixType::Member)
	{}
 
	PostfixExpressionSyntax::PostfixExpressionSyntax(PostfixExpressionSyntax&& other) :
	_expression(std::move(other._expression)),
	_type(other._type)
	{
		switch (_type)
		{
			case PostfixType::Index:
				new(&_index) auto(std::move(other._index));
				break;

			case PostfixType::FunctionCall:
				new(&_arguments) auto(std::move(other._arguments));
				break;

			case PostfixType::Member:
				new (&_member) auto(std::move(other._member));
				break;
		}
	}

	PostfixExpressionSyntax::~PostfixExpressionSyntax()
	{
		switch (_type)
		{
			case PostfixType::Index:
				_index.~ExpressionSyntax();
				break;

			case PostfixType::FunctionCall:
				_arguments.~vector();
				break;

			case PostfixType::Member:
				_member.~IdentifierSyntax();
				break;
		}
	}

	StatementSyntax::StatementSyntax(AssignmentSyntax&& assignment) :
	_assignment(new AssignmentSyntax(std::move(assignment))),
	_type(StatementType::Assignment)
	{}

	StatementSyntax::StatementSyntax(ExpressionStatementSyntax&& statement) :
	_expression(new ExpressionStatementSyntax(std::move(statement))),
	_type(StatementType::Expression)
	{}

	StatementSyntax::StatementSyntax(BlockStatementSyntax&& block) :
	_block(new BlockStatementSyntax(std::move(block))),
	_type(StatementType::Block)
	{}

	StatementSyntax::StatementSyntax(DeclarationSyntax&& variable) :
	_declaration(new DeclarationSyntax(std::move(variable))),
	_type(StatementType::Declaration)
	{}

	StatementSyntax::StatementSyntax(IfStatementSyntax&& if_statement) :
	_iff(new IfStatementSyntax(std::move(if_statement))),
	_type(StatementType::If)
	{}

	StatementSyntax::StatementSyntax(StatementSyntax&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case StatementType::Assignment:
				new (&_assignment) auto(std::move(other._assignment));
				break;

			case StatementType::Expression:
				new (&_expression) auto(std::move(other._expression));
				break;

			case StatementType::Block:
				new (&_block) auto(std::move(other._block));
				break;

			case StatementType::Declaration:
				new (&_declaration) auto(std::move(other._declaration));
				break;

			case StatementType::If:
				new (&_iff) auto(std::move(other._iff));
				break;
		}
	}

	StatementSyntax::~StatementSyntax()
	{
		switch (_type)
		{
			case StatementType::Assignment:
				delete _assignment;
				break;
				
			case StatementType::Expression:
				delete _expression;
				break;
				
			case StatementType::Block:
				delete _block;
				break;
				
			case StatementType::Declaration:
				delete _declaration;
				break;
				
			case StatementType::If:
				delete _iff;
				break;
			}
	}

	IfStatementSyntax::IfStatementSyntax(ExpressionSyntax&& condition, BlockStatementSyntax&& then_body) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_type(IfType::Then)
	{}

	IfStatementSyntax::IfStatementSyntax(ExpressionSyntax&& condition, BlockStatementSyntax&& then_body, BlockStatementSyntax&& else_body) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_else_body(std::move(else_body)),
	_type(IfType::ThenElse)
	{}

	IfStatementSyntax::IfStatementSyntax(ExpressionSyntax&& condition, BlockStatementSyntax&& then_body, IfStatementSyntax *else_if) :
	_condition(std::move(condition)),
	_then_body(std::move(then_body)),
	_else_if(std::move(else_if)),
	_type(IfType::ThenElse)
	{}

	IfStatementSyntax::IfStatementSyntax(IfStatementSyntax&& other) :
	_condition(std::move(other._condition)),
	_then_body(std::move(other._then_body)),
	_type(other._type)
	{
		switch (_type)
		{
			case IfType::Then:
				break;

			case IfType::ThenElse:
				new(&_else_body) auto(std::move(other._else_body));
				break;

			case IfType::ThenElseIf:
				_else_if = other._else_if;
				other._else_if = nullptr;
				break;
		}
	}

	IfStatementSyntax::~IfStatementSyntax()
	{
		if (_type == IfType::ThenElse)
		{
			_else_body.~BlockStatementSyntax();
		}
		else if (_type == IfType::ThenElse)
		{
			delete _else_if;
		}
	}

	TypeDefinitionSyntax::TypeDefinitionSyntax(IdentifierSyntax&& name, StructSyntax&& struct_def) :
	_name(std::move(name)),
	_struct(std::move(struct_def)),
	_type(TypeDefinitionType::Struct)
	{}

	TypeDefinitionSyntax::TypeDefinitionSyntax(TypeDefinitionSyntax&& other) :
	_name(std::move(other._name)),
	_type(other._type)
	{
		switch (_type)
		{
			case TypeDefinitionType::Struct:
				new (&_struct) auto(std::move(other._struct));
				break;			
		}
	}

	TypeDefinitionSyntax::~TypeDefinitionSyntax()
	{
		switch (_type)
		{
			case TypeDefinitionType::Struct:
				_struct.~StructSyntax();
				break;			
		}
	}
}
