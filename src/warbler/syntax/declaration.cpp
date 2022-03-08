#include <warbler/syntax/statement/declaration.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Declaration::Declaration(Identifier&& name, Optional<Type>&& type, bool is_mutable) :
	_name(std::move(name)),
	_type(std::move(type)),
	_is_mutable(is_mutable)
	{}

	Result<Declaration> Declaration::parse(lexicon::Token& token)
	{
		auto is_mutable = false;

		if (token.type() == lexicon::TokenType::KeywordMut)
		{
			is_mutable = true;
			token.next();
		}

		auto name = Identifier::parse(token);
		
		if (!name)
			return {};

		Optional<Type> type;

		if (token.type() == lexicon::TokenType::Colon)
		{
			auto res = Type::parse(token.next());

			if (!res)
				return {};

			type = res.unwrap();
		}

		return Declaration { name.unwrap(), std::move(type), is_mutable };
	}

	// bool Declaration::validate_parameter(semantics::Context& context, semantics::FunctionContext& func_ctx)
	// {
	// 	auto *previous_declaration = func_ctx.get_parameter(_name.text());

	// 	if (previous_declaration)
	// 	{
	// 		print_error(_name.token(), "parameter '" + _name.text() + "' is previously declared in function '" + func_ctx.name + "'");
	// 		print_note(previous_declaration->name().token(), "previous declaration is here");
	// 		return false;
	// 	}

	// 	func_ctx.parameters[_name.text()] = this;
	// 	_type.validate(mod_ctx);

	// 	return true;
	// }

	// bool Declaration::validate_variable(semantics::Context& context, semantics::FunctionContext& func_ctx)
	// {
	// 	auto *previous_declaration = func_ctx.current_block().get_variable(_name.text());

	// 	if (previous_declaration)
	// 	{
	// 		print_error(_name.token(), "'" + _name.text() + "' is previously declared as a variable in scope");
	// 		print_note(previous_declaration->name().token(), "previous declaration here");
	// 		return false;
	// 	}

	// 	auto is_base_scope = func_ctx.blocks.size() == 1;

	// 	if (is_base_scope)
	// 	{
	// 		previous_declaration = func_ctx.get_parameter(_name.text());

	// 		if (previous_declaration)
	// 		{
	// 			print_error(_name.token(), "'" + _name.text() + "' is previously declared as a parameter in function '" + func_ctx.name + "'");
	// 			print_note(previous_declaration->name().token(), "previous declaration here");
	// 			return false;
	// 		}
	// 	}

	// 	func_ctx.current_block().variables[_name.text()] = this;
	// 	_type.validate(mod_ctx);

	// 	return true;
	// }

	// void Declaration::print_tree(u32 depth) const
	// {
		// String text = _is_mutable
		// 	? "mut "
		// 	: "";

		// text += _name.token().text() + ": " + (_type.has_value() ? _type->base_type().text() : "<auto>");

		// print_branch(depth, text);
	// }
}
