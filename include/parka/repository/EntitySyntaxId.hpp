// #ifndef PARKA_ENTITY_ENTITY_ID_HPP
// #define PARKA_ENTITY_ENTITY_ID_HPP

// #include "parka/enum/EntityType.hpp"
// #include "parka/util/Common.hpp"
// #include "parka/util/View.hpp"

// #include <ostream>

// namespace parka
// {
// 	class EntityAstId
// 	{
// 		u32 _index;
// 		EntityType _type;

// 	private:

// 		EntityAstId(EntityType type, usize index) :
// 		_index(index),
// 		_type(type)
// 		{}

// 	public: 

// 		EntityAstId(EntityAstId&&) = default;
// 		EntityAstId(const EntityAstId&) = default;

// 		const auto& type() const { return _type; }
// 		const auto& index() const { return _index; }

// 		EntityAstId& operator=(EntityAstId&& other) = default;
// 		EntityAstId& operator=(const EntityAstId& other) = default;
// 		friend std::ostream& operator<<(std::ostream& out, const EntityAstId& id);
// 		bool operator==(const EntityAstId& other) const;

// 		friend struct EntityAst;
// 		friend class std::hash<EntityAstId>;
// 	};
// }

// namespace std
// {
// 	template <>
// 	struct hash<parka::EntityAstId>
// 	{
// 		parka::usize operator()(const parka::EntityAstId& key) const;
// 	};
// }

// #endif
