// #include "parka/repository/EntityContextId.hpp"
// #include "parka/enum/EntityType.hpp"
// #include "parka/intrinsic/Primitive.hpp"
// #include "parka/log/Log.hpp"
// #include "parka/repository/EntityContext.hpp"
// #include "parka/util/Pool.hpp"

// namespace parka
// {
// 	bool EntityContextId::operator==(const EntityContextId& other)
// 	{
// 		return _index == other._index && _type == other._type;
// 	}

// 	std::ostream& operator<<(std::ostream& out, const EntityContextId& id)
// 	{
// 		out << id.type() << "s[" << id.index() << ']';

// 		return out;
// 	}
// }
