#include <warbler/ast/expression/postfix.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/expression/expression.hpp>

// standard headers
#include <cassert>
#include <cstdlib>

namespace warbler
{
	Postfix::Postfix(Expression *index) :
	_index(index),
	_type(POSTFIX_INDEX)
	{}
	
	Postfix::Postfix(std::vector<Argument>&& arguments) :
	_arguments(arguments),
	_type(POSTFIX_FUNCTION_CALL)
	{}
	
	Postfix::Postfix(Identifier&& member) :
	_member(member),
	_type(POSTFIX_MEMBER)
	{}
	
	Postfix::Postfix(Postfix&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case POSTFIX_INDEX:
				_index = other._index;
				break;

			case POSTFIX_FUNCTION_CALL:
				_arguments = std::move(other._arguments);
				break;

			case POSTFIX_MEMBER:
				_member = std::move(other._member);
				break;
		}

		other._index = nullptr;
		other._type = POSTFIX_INDEX;
	}

	Postfix::Postfix(const Postfix& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case POSTFIX_INDEX:
				_index = new Expression(*other._index);
				break;

			case POSTFIX_FUNCTION_CALL:
				_arguments = other._arguments;
				break;

			case POSTFIX_MEMBER:
				_member = other._member;
				break;
		}
	}


	Postfix::~Postfix()
	{
		if (_type == POSTFIX_INDEX)
		{
			delete _index;
		}
		else if (_type == POSTFIX_FUNCTION_CALL)
		{
			_arguments.~vector();
		}
		else
		{
			_member.~Identifier();
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

				if (index.has_error())
					return index.error();

				iter += 1;

				if (iter->type() != TOKEN_RBRACK)
				{
					error_out(iter) << "expected ']' after index operation but got: " << *iter << std::endl;
					return ERROR_ARGUMENT;
				}

				return Postfix(new Expression(index.unwrap()));
			}
			case TOKEN_LPAREN:
			{
				auto arguments = Argument::parse_list(iter);

				if (arguments.has_error())
					return arguments.error();

				return Postfix(arguments.unwrap());
			}
			case TOKEN_DOT:
			{
				iter += 1;

				auto member = Identifier::parse(iter);

				if (member.has_error())
					return member.error();

				return Postfix(member.unwrap());
			}
			default:
				break;
		}

		return ERROR_NOT_FOUND;
	}

	Result<std::vector<Postfix>> Postfix::parse_list(TokenIterator& iter)
	{
		std::vector<Postfix> out;

		while (true)
		{
			auto res = Postfix::parse(iter);

			if (res.has_error())
			{
				if (res.error() == ERROR_NOT_FOUND)
					break;

				return res.error();
			}

			out.emplace_back(res.unwrap());
		}

		return out;
	}

	void Postfix::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);

		switch (_type)
		{
			case POSTFIX_INDEX:
				std::cout << "[]\n";
				_index->print_tree(depth + 1);
				break;

			case POSTFIX_FUNCTION_CALL:
				std::cout << "()\n";

				for (const auto& arg : _arguments)
					arg.print_tree(depth + 1);
				break;

			case POSTFIX_MEMBER:
				std::cout << ".\n";
				_member.print_tree(depth + 1);
				break;
		}
	}

	Postfix& Postfix::operator=(Postfix&& other)
	{
		_type = other._type;
		
		switch (_type)
		{
			case POSTFIX_INDEX:
				_index = other._index;
				break;

			case POSTFIX_FUNCTION_CALL:
				_arguments = std::move(other._arguments);
				break;

			case POSTFIX_MEMBER:
				_member = std::move(other._member);
				break;
		}

		other._type = POSTFIX_INDEX;
		other._index = nullptr;

		return *this;
	}

	Postfix& Postfix::operator=(const Postfix& other)
	{
		_type = other._type;

		switch (_type)
		{
			case POSTFIX_INDEX:
				_index = new Expression(*other._index);
				break;

			case POSTFIX_FUNCTION_CALL:
				_arguments = other._arguments;
				break;

			case POSTFIX_MEMBER:
				_member = other._member;
				break;
		}

		return *this;
	}
}