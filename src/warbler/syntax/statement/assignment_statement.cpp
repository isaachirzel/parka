#include <warbler/syntax//statement/assignment_statement.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler::syntax
{
	AssignmentStatement::AssignmentStatement(Ptr<Expression>&& lhs, Ptr<Expression>&& rhs, AssignmentType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

	Result<AssignmentStatement> AssignmentStatement::parse(TokenIterator& iter)
	{
		auto lhs = PrefixExpression::parse(iter);

		if (!lhs)
			return {};

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
				parse_error(iter, "expected assignment operator after primary expression");
				return {};
		}

		++iter;

		auto rhs = Expression::parse(iter);

		if (!rhs)
			return {};

		return AssignmentStatement(lhs.unwrap(), rhs.unwrap(), type);
	}

	bool AssignmentStatement::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		throw std::runtime_error("AssignmentStatement::validate is not implemented yet");
	}

	void AssignmentStatement::print_tree(u32 depth) const
	{
		_lhs->print_tree(depth);

		std::cout << tree_branch(depth);

		switch (_type)
		{
			case ASSIGN_BECOME:
				std::cout << "=\n";
				break;

			case ASSIGN_MULTIPLY:
				std::cout << "*=\n";
				break;

			case ASSIGN_DIVIDE:
				std::cout << "/=\n";
				break;

			case ASSIGN_MODULUS:
				std::cout << "%=\n";				
				break;

			case ASSIGN_ADD:
				std::cout << "*=\n";
				break;

			case ASSIGN_SUBTRACT:
				std::cout << "-=\n";
				break;

			case ASSIGN_LSHIFT:
				std::cout << "<<=\n";
				break;

			case ASSIGN_RSHIFT:
				std::cout << ">>=\n";
				break;

			case ASSIGN_BITWISE_AND:
				std::cout << "&=\n";
				break;

			case ASSIGN_BITWISE_OR:
				std::cout << "|=\n";
				break;

			case ASSIGN_BITWISE_XOR:
				std::cout << "^=\n";
				break;
		}

		_rhs->print_tree(depth + 1);
	}
}
