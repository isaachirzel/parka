// header
#include <grackle/node/identifier.h>

// local includes
#include <exception/util.h>

namespace grackle
{
	Identifier::Identifier(const std::vector<Token>::iterator &iter)
	{
		throw NotImplementedError(__func__);
	}
	
	void Identifier::verify() const
	{
		throw NotImplementedError(__func__);
	}

	void Identifier::print_tree() const
	{
		throw NotImplementedError(__func__);
	}

	std::string Identifier::to_c() const
	{
		throw NotImplementedError(__func__);
	}
}
