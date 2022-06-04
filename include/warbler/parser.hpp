#ifndef WARBLER_PARSER_HPP
#define WARBLER_PARSER_HPP

#include <warbler/syntax.hpp>
#include <warbler/directory.hpp>

namespace warbler
{
	// Expression
	Result<ExpressionSyntax> parse_additive_expression(Token& token);
	Result<ExpressionSyntax> parse_additive_expression(Token& token);
	Result<ExpressionSyntax> parse_bitwise_and_expression(Token& token);
	Result<ExpressionSyntax> parse_bitwise_or_expression(Token& token);
	Result<ExpressionSyntax> parse_bitwise_xor_expression(Token& token);
	Result<ExpressionSyntax> parse_boolean_and_expression(Token& token);
	Result<ExpressionSyntax> parse_boolean_or_expression(Token& token);
	Result<ExpressionSyntax> parse_conditional_expression(Token& token);
	Result<ExpressionSyntax> parse_equality_expression(Token& token);
	Result<ExpressionSyntax> parse_multiplicative_expression(Token& token);
	Result<ExpressionSyntax> parse_postfix_expression(Token& token);
	Result<ExpressionSyntax> parse_prefix_expression(Token& token);
	Result<ExpressionSyntax> parse_primary_expression(Token& token);
	Result<ExpressionSyntax> parse_relational_expression(Token& token);
	Result<ExpressionSyntax> parse_bit_shift_expression(Token& token);
	Result<ExpressionSyntax> parse_symbol(Token& token);
	Result<ExpressionSyntax> parse_constant(Token& token);
	inline Result<ExpressionSyntax> parse_expression(Token& token) { return parse_conditional_expression(token); }

	// Function
	Result<FunctionSyntax> parse_function(Token& token);
	Result<Array<ExpressionSyntax>> parse_arguments(Token& token);
	Result<ParameterSyntax> parse_parameter(Token& token);
	Result<Array<ParameterSyntax>> parse_parameter_list(Token& token);
	Result<FunctionSignatureSyntax> parse_function_signature(Token& token);

	// Statement
	Result<AssignmentSyntax> parse_assignment(Token& token);
	Result<BlockStatementSyntax> parse_block_statement(Token& token);
	Result<DeclarationSyntax> parse_declaration(Token& token);
	Result<ExpressionStatementSyntax> parse_expression_statement(Token& token);
	Result<IfStatementSyntax> parse_if_statement(Token& token);
	Result<StatementSyntax> parse_statement(Token& token);

	// Type
	Result<TypeSyntax> parse_type(Token& token);
	Result<MemberSyntax> parse_member(Token& token);
	Result<StructSyntax> parse_struct(Token& token);
	Result<LabelSyntax> parse_label(Token& token);
	Result<TypeAnnotationSyntax> parse_type_annotation(Token& token);
	Result<VariableSyntax> parse_variable(Token& token);
	Result<PackageSyntax> parse_module(Token& token);
	Result<ProgramSyntax> parse(const Array<Directory>& directories);
}

#endif
