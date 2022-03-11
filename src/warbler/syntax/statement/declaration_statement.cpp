#include <warbler/syntax/statement/declaration_statement.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	VariableStatement::VariableStatement(Variable&& declaration, Expression&& value) :
	_declaration(std::move(declaration)),
	_value(std::move(value))
	{}

	Result<VariableStatement> VariableStatement::parse(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::KeywordVar)
		{
			print_parse_error(token, "var");
			return {};
		}
		
		auto declaration = Variable::parse(token.next());

		if (!declaration)
			return {};

		if (token.type() != lexicon::TokenType::Assign)
		{
			print_parse_error(token, "expected '=' after declaration");
			return {};
		}

		auto value = Expression::parse(token.next());

		if (!value)
			return {};

		if (token.type() != lexicon::TokenType::Semicolon)
		{
			print_parse_error(token, "expected ';' after declaration");
			return {};
		}

		token.next();

		return VariableStatement { declaration.unwrap(), value.unwrap() };
	}

	// bool VariableStatement::validate(semantics::Context& context)
	// {
	// 	if (!_declaration.validate_variable(mod_ctx, func_ctx) && _value->validate(mod_ctx, func_ctx))
	// 		return false;

	// 	auto& decl_type = _declaration.type();

	// 	if (!decl_type.is_auto())
	// 	{
	// 		auto *expr_type = _value->get_type();

	// 		if (!decl_type.validate_cast_from(expr_type))
	// 			return false;
	// 	}

	// 	return true;
	// }

	// void VariableStatement::print_tree(u32 depth) const
	// {
	// 	_declaration.print_tree(depth);
	// 	print_branch(depth + 1, "=");
	// 	_value->print_tree(depth  + 2);
	// }
}