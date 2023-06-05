#ifndef PARKA_ENTITY_ENTITY_ID_HPP
#define PARKA_ENTITY_ENTITY_ID_HPP

#include "parka/syntax/EntitySyntax.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/View.hpp"

#include <ostream>

namespace parka
{
	class PackageSyntax;
	class Primitive;
	class StructSyntax;
	class FunctionSyntax;
	class VariableSyntax;
	class ParameterSyntax;

	class EntitySyntaxId
	{
		u32 _index;
		EntityType _type;

		EntitySyntaxId(EntityType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:

		static const EntitySyntaxId voidId;
		static const EntitySyntaxId u8Id;
		static const EntitySyntaxId u16Id;
		static const EntitySyntaxId u32Id;
		static const EntitySyntaxId u64Id;
		static const EntitySyntaxId i8Id;
		static const EntitySyntaxId i16Id;
		static const EntitySyntaxId i32Id;
		static const EntitySyntaxId i64Id;
		static const EntitySyntaxId f32Id;
		static const EntitySyntaxId f64Id;
		static const EntitySyntaxId boolId;
		static const EntitySyntaxId charId;
		static const EntitySyntaxId stringId;

	public: 

		EntitySyntaxId(EntitySyntaxId&&) = default;
		EntitySyntaxId(const EntitySyntaxId&) = default;

		static EntitySyntaxId create(PackageSyntax&&);
		static EntitySyntaxId create(StructSyntax&&);
		static EntitySyntaxId create(FunctionSyntax&&);
		static EntitySyntaxId create(VariableSyntax&&);
		static EntitySyntaxId create(ParameterSyntax&&);

		static EntitySyntaxId getFor(const PackageSyntax&);
		static EntitySyntaxId getFor(const FunctionSyntax&);
		static EntitySyntaxId getFor(const Primitive&);

		const PackageSyntax& getPackage() const;
		const Primitive& getPrimitive() const;
		const StructSyntax& getStruct() const;
		const FunctionSyntax& getFunction() const;
		const VariableSyntax& getVariable() const;
		const ParameterSyntax& getParameter() const;

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }

		EntitySyntaxId& operator=(EntitySyntaxId&& other) = default;
		EntitySyntaxId& operator=(const EntitySyntaxId& other) = default;
		friend std::ostream& operator<<(std::ostream& out, const EntitySyntaxId& id);
		bool operator==(const EntitySyntaxId& other) const;
		const EntitySyntax& operator*() const;
		const EntitySyntax *operator->() const;

		friend std::ostream& operator<<(std::ostream& out, const EntitySyntaxId& id);
		friend class std::hash<EntitySyntaxId>;
	};
}

namespace std
{
	template <>
	struct hash<parka::EntitySyntaxId>
	{
		parka::usize operator()(const parka::EntitySyntaxId& key) const;
	};
}

#endif
