#include <warbler/syntax/type.hpp>

// standard headers
#include <warbler/util/print.hpp>
#include <warbler/syntax/type/primitive.hpp>

namespace warbler::syntax
{
	Type::Type() {}

	Type::Type(const source::Location& location, String&& base_name, Array<bool>&& ptr_mutability) :
	_location(location),
	_base_name(std::move(base_name)),
	_ptr_mutability(std::move(ptr_mutability)),	
	_is_auto(false)
	{}

	Type::Type(String&& base_name, TypeDefinition *definition) :
	_base_name(base_name),
	_definition(definition),
	_is_auto(false)
	{}

	Result<Type> Type::parse(lexicon::TokenIterator& iter)
	{
		Array<bool> ptr_mutability;

		const source::Location start_location = iter->location();

		while (iter->type() == lexicon::TOKEN_ASTERISK)
		{
			iter += 1;

			if (iter->type() == lexicon::TOKEN_MUT)
			{
				ptr_mutability.push_back(true);
				iter += 1;
			}
			else
			{
				ptr_mutability.push_back(false);
			}
		}

		if (iter->type() != lexicon::TOKEN_IDENTIFIER)
		{
			print_parse_error(iter, "typename");
			return {};
		}
		
		const auto& end_location = iter->location();

		iter += 1;

		return Type { start_location + end_location, end_location.text(), std::move(ptr_mutability) };
	}

	bool Type::validate(semantics::ModuleContext& context)
	{
		if (!_is_auto)
		{
			_definition = context.get_type(_base_name);

			if (_definition == nullptr)
			{
				print_error(_location, "'" + _base_name + "' is not an imported or locally defined type");
				return false;
			}
		}

		return true;
	}

	char value()
	{
		i64 value = 23;
		return value;
	}

	bool Type::validate_cast_from( Type* other)
	{
		auto *other_primitive = dynamic_cast<Primitive*>(other->definition());

		if (other_primitive != nullptr)
		{
			auto *primitive = dynamic_cast<Primitive*>(_definition);

			if (primitive == nullptr || primitive->type() != other_primitive->type())
			{
				print_error(other->_location, "primitive '" + other->_base_name + "' cannot be cast to type '" + _base_name + "'");
				return false;
			}

			if (primitive->bytes() < other_primitive->bytes())
			{
				print_error(_location, "cast from '" + other->_base_name + "' to '" + _base_name + "' truncates value and may not fit");
				return false;
			}
		}
		else if (_definition != other->_definition)
		{
			print_error(_location, "type '" + _base_name + "' cannot be implicitly cast to type '" + other->_base_name + "'");
			print_note(other->_location, "type '" + other->_base_name + "' declared here");
			return false;
		}

		return true;
	}

	void Type::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << ": " <<  _base_name << '\n';
	}

	String Type::text() const
	{
		if (_is_auto)
			return "<auto>";


		usize size = _base_name.size();

		for (const auto& is_mut : _ptr_mutability)
		{
			size += 1 + is_mut * 4;
		}

		String out;
		out.reserve(size);

		for (const auto& is_mut : _ptr_mutability)
		{
			out += '*';

			if (is_mut)
			{
				out += "mut ";
			}
		}

		out += _base_name;

		return out;
	}
}
