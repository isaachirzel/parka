#include "parka/repository/EntityContextId.hpp"
#include "parka/context/PackageContext.hpp"
#include "parka/enum/EntityType.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/util/Pool.hpp"

namespace parka
{
	static Pool<PackageContext> packages(10'000);

	static usize insertEntityContext(EntityType type, EntityContext&& context)
	{
		switch (type)
		{
			case EntityType::Package:
				return packages.add(std::move((PackageContext&&)context));
			
			default:
				break;
		}

		log::fatal("Unable to create EntityContextId for EntityContext with type: $", type);
	}

	static usize getEntityContextIndex(const EntityType type, const EntityContext& context)
	{
		switch (type)
		{

			case EntityType::Package:
				return packages.getIndex((const PackageContext*)&context);
				
			case EntityType::Struct:
				break;

			case EntityType::Primitive:
				return Primitive::primitives.getIndex((const Primitive*)&context);
				
			case EntityType::Function:
				break;

			case EntityType::Variable:
				break;

			case EntityType::Parameter:
				break;

			default:
				break;
		}

		log::fatal("Unable to get EntityContextId for EntityContext with type: $", type);
	}

	EntityContextId EntityContextId::create(EntityContext&& context)
	{
		auto type = context.type();
		auto index = insertEntityContext(type, std::move(context));

		return EntityContextId(type, index);
	}

	EntityContextId EntityContextId::get(const EntityContext& context)
	{
		const auto type = context.type();
		const auto index = getEntityContextIndex(type, context);

		return EntityContextId(type, index);
	}

	bool EntityContextId::operator==(const EntityContextId& other)
	{
		return _index == other._index && _type == other._type;
	}

	const EntityContext& EntityContextId::operator*() const
	{
		log::notImplemented(here());
	}

	const EntityContext *EntityContextId::operator->() const
	{
		return &(*(*this));
	}

	std::ostream& operator<<(std::ostream& out, const EntityContextId& id)
	{
		out << id.type() << "s[" << id.index() << ']';

		return out;
	}
}
