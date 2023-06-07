#ifndef PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP
#define PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP

#include "parka/enum/PrimitiveType.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"
#include "parka/util/View.hpp"

namespace parka
{
	class Primitive : public EntitySyntax, public EntityContext
	{
		String _identifier;
		PrimitiveType _type;
		u32 _size;

		Primitive(const char *identifier, PrimitiveType type, u32 size) :
		_identifier(identifier),
		_type(type),
		_size(size)
		{}

		static Array<Primitive> initPrimitives();

	public:

		static const Array<Primitive> primitives;

	public:

		Primitive(Primitive&&) = default;
		Primitive(const Primitive&) = delete;

		const String& identifier() const { return _identifier; }
		EntityType type() const { return EntityType::Primitive; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
