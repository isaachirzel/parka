#include <warbler/syntax/function/function.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Function::Function(Identifier&& name, FunctionSignature&& signature, BlockStatement&& body) :
	_name(std::move(name)),
	_signature(std::move(signature)),
	_body(std::move(body))
	{}

	Result<Function> Function::parse(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::KeywordFunction)
		{
			print_parse_error(token, "'function'");
			return {};
		}

		auto name = Identifier::parse(token.next());

		if (!name)
			return {};

		auto signature = FunctionSignature::parse(token);

		if (!signature)
			return {};

		if (token.type() != lexicon::TokenType::LeftBrace)
		{
			print_parse_error(token, "function body");
			return {};
		}
	
		auto body = BlockStatement::parse(token);

		if (!body)
			return {};

		return Function(name.unwrap(), signature.unwrap(), body.unwrap());
	}

	// bool Function::validate(semantics::ModuleContext& mod_ctx)
	// {
	// 	_context.blocks.push_back(&_body.context());

	// 	for (auto& parameter : _parameters)
	// 	{
	// 		if (!parameter.validate_parameter(mod_ctx, _context))
	// 			return false;
	// 	}

	// 	return _return_type.validate(mod_ctx) && _body.validate(mod_ctx, _context);
	// }

	void Function::print_tree(u32 depth) const 
	{
		print_branch(depth, "function " + _name.token().text());
		print_branch(depth + 1, "function signature printing is not implemented");

		_body.print_tree(depth + 1);
	}
}