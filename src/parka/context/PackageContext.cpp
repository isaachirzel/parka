#include "parka/context/PackageContext.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	void PackageContext::validate(Array<EntityContextId>&, const EntitySyntaxId&)
	{
		log::notImplemented(here());
	}
}
