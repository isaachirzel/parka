#ifndef WARBLER_SEMANTICS_DEFINITION_HPP
#define WARBLER_SEMANTICS_DEFINITION_HPP

#include <warbler/util/string.hpp>
#include <warbler/semantics/type/struct.hpp>
#include <warbler/semantics/type/primitive.hpp>

#include <cassert>

namespace warbler::semantics
{
	enum class DefinitionType
	{
		Primitive,
		Struct
	};

	class Definition
	{
		String _symbol;

		union
		{
			Struct _struct_def;
			Primitive _primitive_def;
		};

		DefinitionType _type;

	public:

		Definition(Struct&& struct_def);
		Definition(Primitive&& primitive_def);
		Definition(Definition&& other);
		Definition(const Definition& other) = delete;
		~Definition();

		const String& symbol() const { return _symbol; }
		DefinitionType type() const { return _type; }
		Struct& struct_def() { assert(_type == DefinitionType::Struct); return _struct_def; }
		Primitive& primitive_def() { assert(_type == DefinitionType::Primitive); return _primitive_def; }
	};
}

#endif
