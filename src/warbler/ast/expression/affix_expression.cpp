#include <warbler/ast/expression/affix_expression.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/ast/expression/primary_expression.hpp>

// standard headers
#include <cassert>
#include <cstdlib>

namespace warbler::ast
{
	AffixExpression::AffixExpression(Array<Prefix>&& prefixes, Ptr<Expression>&& expression, Array<Postfix>&& postfixes) :
	_prefixes(std::move(prefixes)),
	_expression(std::move(expression)),
	_postfixes(std::move(postfixes))
	{}

	Result<AffixExpression> AffixExpression::parse(TokenIterator& iter)
	{
		auto prefixes = Prefix::parse_list(iter);

		auto expression = PrimaryExpression::parse(iter);

		if (!expression)
			return {};

		auto postfixes = Postfix::parse_list(iter);

		if (!postfixes)
			return {};

		return AffixExpression { std::move(prefixes), expression.unwrap(), postfixes.unwrap() };
	}

	bool AffixExpression::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx, bool expect_lvalue)
	{
		#pragma message("TODO: implement reference depth handling in validation")
		#pragma message("TODO: implement type handling in validation")

		if (!_expression->validate(mod_ctx, func_ctx))
		{
			return false;
		}

		auto is_rvalue = false;
		auto reference_depth = 0u; // TODO: infer from type

		for (i32 i = _prefixes.size() - 1; i >= 0; --i)
		{
			const auto& prefix = _prefixes[i];

			switch (prefix.type())
			{
				case PREFIX_REFERENCE:

					// ERROR if ravlue
					// OK for any type

					if (is_rvalue)
					{
						// ERROR cannot take refence of rvalue
						print_error(prefix.location(), "reference cannot be taken of rvalue");
						return false;
					}

					is_rvalue = true;
					reference_depth += 1;
					break;

				case PREFIX_DEREFERENCE:
					if (reference_depth == 0)
					{
						print_error(prefix.location(), "dereferencing may only be done on pointer types");
						return false;
					}

					is_rvalue = false;
					break;

				case PREFIX_POSITIVE:
					is_rvalue = true;

					// ERROR if not integral
					break;

				case PREFIX_NEGATIVE:
					is_rvalue = true;
					// ERROR if not integral
					break;

				case PREFIX_BITWISE_NOT:
					is_rvalue = true;
					// ERROR if not integral or byte
					break;

				case PREFIX_BOOLEAN_NOT:
					is_rvalue = true;
					// ERROR if not boolean-ish					
					break;
			}
		}

		for (auto& postfix : _postfixes)
		{
			if (!postfix.validate(mod_ctx, func_ctx, _expression))
				return false;
		}

		return true;
	}

	void AffixExpression::print_tree(u32 depth) const
	{
		if (_prefixes.size() > 0)
			depth += 1;

		for (const auto& prefix : _prefixes)
			prefix.print_tree(depth - 1);

		_expression->print_tree(depth);

		for (const auto& postfix : _postfixes)
			postfix.print_tree(depth + 1);
	}
}
