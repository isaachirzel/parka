#ifndef PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP
#define PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP

#include "parka/data/EntitySyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/Token.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Primitives.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	enum class PrimitiveType
	{
		Void,
		UnsignedInteger,
		SignedInteger,
		FloatingPoint,
		Boolean,
		Character,
		String
	};

	class Primitive : public EntitySyntax
	{
		String _identifier;
		PrimitiveType _type;
		u32 _size;

		Primitive(const char *identifier, PrimitiveType type, u32 size) :
		_identifier(identifier),
		_type(type),
		_size(size)
		{}

	public:

		Primitive(Primitive&&) = default;
		Primitive(const Primitive&) = delete;
		~Primitive() = default;

		const String& identifier() const { return _identifier; }
		EntityType type() const { return EntityType::Primitive; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }

		friend struct Storage;
	};
}

#endif
