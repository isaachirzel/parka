#include <warbler/ast/expression/postfix.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>

// standard headers
#include <cassert>
#include <cstdlib>

namespace warbler::ast
{
	Postfix::Postfix(Ptr<Expression>&& index) :
	_index(std::move(index)),
	_type(POSTFIX_INDEX)
	{}
	
	Postfix::Postfix(Array<Argument>&& arguments) :
	_arguments(std::move(arguments)),
	_type(POSTFIX_FUNCTION_CALL)
	{}
	
	Postfix::Postfix(Name&& member) :
	_member(std::move(member)),
	_type(POSTFIX_MEMBER)
	{}
	
	Postfix::Postfix(Postfix&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case POSTFIX_INDEX:
				new (&_index) auto(std::move(other._index));
				break;

			case POSTFIX_FUNCTION_CALL:
				new(&_arguments) auto(std::move(other._arguments));
				break;

			case POSTFIX_MEMBER:
				new(&_member) auto(std::move(other._member));
				break;
		}
	}

	Postfix::~Postfix()
	{
		switch (_type)
		{
			case POSTFIX_INDEX:
				_index.~Ptr();
				break;

			case POSTFIX_FUNCTION_CALL:
				_arguments.~vector();
				break;

			case POSTFIX_MEMBER:
				_member.~Name();
				break;
		}		
	}

	Result<Postfix> Postfix::parse(TokenIterator& iter)
	{
		switch (iter->type())
		{
			case TOKEN_LBRACK:
			{
				iter += 1;

				auto index = Expression::parse(iter);

				if (!index)
					return {};

				iter += 1;

				if (iter->type() != TOKEN_RBRACK)
				{
					error_out(iter) << "expected ']' after index operation but got: " << *iter << std::endl;
					return {};
				}

				return Postfix { index.unwrap() };
			}
			case TOKEN_LPAREN:
			{
				auto arguments = Argument::parse_list(iter);

				if (!arguments)
					return {};

				return Postfix { arguments.unwrap() };
			}
			case TOKEN_DOT:
			{
				iter += 1;

				auto member = Name::parse(iter);

				if (!member)
					return {};

				return Postfix(member.unwrap());
			}
			default:
				return {};
		}
	}

	Result<Array<Postfix>> Postfix::parse_list(TokenIterator& iter)
	{
		Array<Postfix> out;

	parse_postfix:		

		switch (iter->type())
		{
			case TOKEN_LBRACK:
			{
				iter += 1;

				auto index = Expression::parse(iter);

				if (!index)
					return {};

				if (iter->type() != TOKEN_RBRACK)
				{
					error_out(iter) << "expected ']' after index operation but got: " << *iter << std::endl;
					return {};
				}

				iter += 1;

				out.emplace_back(Postfix { index.unwrap() });
				goto parse_postfix;
			}

			case TOKEN_LPAREN:
			{
				auto arguments = Argument::parse_list(iter);

				if (!arguments)
					return {};

				out.emplace_back(Postfix { arguments.unwrap() });
				goto parse_postfix;
			}

			case TOKEN_DOT:
			{
				iter += 1;

				auto member = Name::parse(iter);

				if (!member)
					return {};

				out.emplace_back(Postfix { member.unwrap() });
				goto parse_postfix;
			}

			default:
				break;
		}

		return out;
	}

	void Postfix::print_tree(u32 depth) const
	{
		switch (_type)
		{
			case POSTFIX_INDEX:
				std::cout << tree_branch(depth) << "[\n";
				_index->print_tree(depth + 1);
				std::cout << tree_branch(depth) << "]\n";
				break;

			case POSTFIX_FUNCTION_CALL:
				std::cout << tree_branch(depth) << "(\n";

				for (const auto& arg : _arguments)
					arg.print_tree(depth + 1);

				std::cout << tree_branch(depth) << ")\n";
				break;

			case POSTFIX_MEMBER:
				std::cout << '.' << _member.text() << '\n';
				break;
		}
	}

	Postfix& Postfix::operator=(Postfix&& other)
	{
		_type = other._type;
		
		switch (_type)
		{
			case POSTFIX_INDEX:
				_index = std::move(other._index);
				break;

			case POSTFIX_FUNCTION_CALL:
				_arguments = std::move(other._arguments);
				break;

			case POSTFIX_MEMBER:
				_member = std::move(other._member);
				break;
		}

		return *this;
	}
}