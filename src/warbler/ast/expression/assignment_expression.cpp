#include <warbler/ast/expression/assignment_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler
{
	AssignmentExpression::AssignmentExpression(PrimaryExpression&& lhs, ConditionalExpression *rhs, AssignmentType type) :
	_lhs(lhs),
	_rhs(rhs),
	_type(type)
	{}

	Result<AssignmentExpression> AssignmentExpression::parse(TokenIterator& iter)
	{
		auto res = PrimaryExpression::parse(iter);

		if (res.has_error())
			return res.error();

		AssignmentType type;
		switch (iter->type())
		{
			case TOKEN_ASSIGN:
				type = ASSIGN_BECOME;
				break;

			case TOKEN_MULTIPLY_ASSIGN:
				type = ASSIGN_MULTIPLY;
				break;

			case TOKEN_DIVIDE_ASSIGN:
				type = ASSIGN_DIVIDE;
				break;

			case TOKEN_MODULUS_ASSIGN:
				type = ASSIGN_MODULUS;
				break;

			case TOKEN_ADD_ASSIGN:
				type = ASSIGN_ADD;
				break;

			case TOKEN_SUBTRACT_ASSIGN:
				type = ASSIGN_SUBTRACT;
				break;

			case TOKEN_LSHIFT_ASSIGN:
				type = ASSIGN_LSHIFT;
				break;

			case TOKEN_RSHIFT_ASSIGN:
				type = ASSIGN_RSHIFT;
				break;

			case TOKEN_BITAND_ASSIGN:
				type = ASSIGN_BITWISE_AND;
				break;

			case TOKEN_BITOR_ASSIGN:
				type = ASSIGN_BITWISE_OR;
				break;

			case TOKEN_BITXOR_ASSIGN:
				type = ASSIGN_BITWISE_XOR;
				break;

			default:
				type = ASSIGN_NONE;
				return AssignmentExpression(res.unwrap(), nullptr, ASSIGN_NONE);
		}

		++iter;

		auto rhs_res = ConditionalExpression::parse(iter);

		if (rhs_res.has_error())
			return rhs_res.error();

		return AssignmentExpression(res.unwrap(), new ConditionalExpression(rhs_res.unwrap()), type);
	}

	void AssignmentExpression::print_tree(u32 depth) const
	{
		_lhs.print_tree(depth);

		switch (_type)
		{
			case ASSIGN_NONE:
				return;

			case ASSIGN_BECOME:
				print_tree_branch_symbol("=", depth);
				break;

			case ASSIGN_MULTIPLY:
				print_tree_branch_symbol("*=", depth);
				break;

			case ASSIGN_DIVIDE:
				print_tree_branch_symbol("/=", depth);
				break;

			case ASSIGN_MODULUS:
				print_tree_branch_symbol("%=", depth);
				break;

			case ASSIGN_ADD:
				print_tree_branch_symbol("+=", depth);
				break;

			case ASSIGN_SUBTRACT:
				print_tree_branch_symbol("-=", depth);
				break;

			case ASSIGN_LSHIFT:
				print_tree_branch_symbol("<<=", depth);
				break;

			case ASSIGN_RSHIFT:
				print_tree_branch_symbol(">>=", depth);
				break;

			case ASSIGN_BITWISE_AND:
				print_tree_branch_symbol("&=", depth);
				break;

			case ASSIGN_BITWISE_OR:
				print_tree_branch_symbol("|=", depth);
				break;

			case ASSIGN_BITWISE_XOR:
				print_tree_branch_symbol("^=", depth);
				break;
		}

		_rhs->print_tree(depth + 1);
	}
}
