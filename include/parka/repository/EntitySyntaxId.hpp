// #ifndef PARKA_ENTITY_ENTITY_ID_HPP
// #define PARKA_ENTITY_ENTITY_ID_HPP

// #include "parka/enum/EntityType.hpp"
// #include "parka/util/Common.hpp"
// #include "parka/util/View.hpp"

// #include <ostream>

// namespace parka
// {
// 	class EntitySyntaxId
// 	{
// 		u32 _index;
// 		EntityType _type;

// 	private:

// 		EntitySyntaxId(EntityType type, usize index) :
// 		_index(index),
// 		_type(type)
// 		{}

// 	public: 

// 		EntitySyntaxId(EntitySyntaxId&&) = default;
// 		EntitySyntaxId(const EntitySyntaxId&) = default;

// 		const auto& type() const { return _type; }
// 		const auto& index() const { return _index; }

// 		EntitySyntaxId& operator=(EntitySyntaxId&& other) = default;
// 		EntitySyntaxId& operator=(const EntitySyntaxId& other) = default;
// 		friend std::ostream& operator<<(std::ostream& out, const EntitySyntaxId& id);
// 		bool operator==(const EntitySyntaxId& other) const;

// 		friend struct EntitySyntax;
// 		friend class std::hash<EntitySyntaxId>;
// 	};
// }

// namespace std
// {
// 	template <>
// 	struct hash<parka::EntitySyntaxId>
// 	{
// 		parka::usize operator()(const parka::EntitySyntaxId& key) const;
// 	};
// }

// #endif
