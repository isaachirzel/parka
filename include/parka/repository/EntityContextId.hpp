// #ifndef PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP
// #define PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP

// #include "parka/enum/Entity.hpp"
// #include "parka/util/Common.hpp"

// namespace parka
// {
// 	class EntityContextId
// 	{
// 		usize _index;
// 		EntityType _type;

// 	private:

// 		EntityContextId(EntityType type, usize index) :
// 		_index(index),
// 		_type(type)
// 		{}

// 	public:

// 		EntityContextId(EntityContextId&&) = default;
// 		EntityContextId(const EntityContextId&) = default;

// 		const auto& type() const { return _type; }
// 		const auto& index() const { return _index; }
		
// 		EntityContextId& operator=(EntityContextId&&) = default;
// 		EntityContextId& operator=(const EntityContextId&) = default;
// 		bool operator==(const EntityContextId&);
// 		// const EntityContext& operator*() const;
// 		// const EntityContext *operator->() const;
// 		friend std::ostream& operator<<(std::ostream& out, const EntityContextId& id);

// 		friend struct EntityContext;
// 	};
// };

// #endif
