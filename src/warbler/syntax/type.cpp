#include <warbler/syntax/type.hpp>

// standard headers
#include <warbler/util/print.hpp>
#include <warbler/syntax/type/primitive.hpp>

namespace warbler::syntax
{
	Type::Type(const source::Location& base_type, Array<PtrLocation>&& ptrs) :
	_base_type(base_type),
	_ptrs(ptrs)
	{}

	Result<Type> Type::parse(lexicon::TokenIterator& iter)
	{
		Array<bool> ptr_mutability;

		const source::Location start_location = iter->location();

		while (iter->type() == lexicon::TokenType::Asterisk)
		{
			iter += 1;

			if (iter->type() == lexicon::TokenType::KeywordMut)
			{
				ptr_mutability.push_back(true);
				iter += 1;
			}
			else
			{
				ptr_mutability.push_back(false);
			}
		}

		if (iter->type() != lexicon::TokenType::Identifier)
		{
			print_parse_error(iter, "type");
			return {};
		}
		
		const auto& base_type = iter->location();

		iter += 1;

		#pragma message "fix parsing of Type"
		return Type { base_type, {} };
	}

	// bool Type::validate(semantics::ModuleContext& context)
	// {
	// 	if (!_is_auto)
	// 	{
	// 		_definition = context.get_type(_base_name);

	// 		if (_definition == nullptr)
	// 		{
	// 			print_error(_location, "'" + _base_name + "' is not an imported or locally defined type");
	// 			return false;
	// 		}
	// 	}

	// 	return true;
	// }

	// bool Type::validate_cast_from( Type* other)
	// {
	// 	auto *other_primitive = dynamic_cast<Primitive*>(other->definition());

	// 	if (other_primitive != nullptr)
	// 	{
	// 		auto *primitive = dynamic_cast<Primitive*>(_definition);

	// 		if (primitive == nullptr || primitive->type() != other_primitive->type())
	// 		{
	// 			print_error(other->_location, "primitive '" + other->_base_name + "' cannot be cast to type '" + _base_name + "'");
	// 			return false;
	// 		}

	// 		if (primitive->bytes() < other_primitive->bytes())
	// 		{
	// 			print_error(_location, "cast from '" + other->_base_name + "' to '" + _base_name + "' truncates value and may not fit");
	// 			return false;
	// 		}
	// 	}
	// 	else if (_definition != other->_definition)
	// 	{
	// 		print_error(_location, "type '" + _base_name + "' cannot be implicitly cast to type '" + other->_base_name + "'");
	// 		print_note(other->_location, "type '" + other->_base_name + "' declared here");
	// 		return false;
	// 	}

	// 	return true;
	// }

	void Type::print_tree(u32 depth) const
	{
		print_branch(depth, ": " + _base_type.text());
	}

	// String Type::text() const
	// {
	// 	if (_is_auto)
	// 		return "<auto>";


	// 	usize size = _base_name.size();

	// 	for (const auto& is_mut : _ptr_mutability)
	// 	{
	// 		size += 1 + is_mut * 4;
	// 	}

	// 	String out;
	// 	out.reserve(size);

	// 	for (const auto& is_mut : _ptr_mutability)
	// 	{
	// 		out += '*';

	// 		if (is_mut)
	// 		{
	// 			out += "mut ";
	// 		}
	// 	}

	// 	out += _base_name;

	// 	return out;
	// }
}
