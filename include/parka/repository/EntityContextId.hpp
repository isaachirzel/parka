// #ifndef PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP
// #define PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP

// #include "parka/enum/Entity.hpp"
// #include "parka/util/Common.hpp"

// namespace parka
// {
// 	class EntityIrId
// 	{
// 		usize _index;
// 		EntityType _type;

// 	private:

// 		EntityIrId(EntityType type, usize index) :
// 		_index(index),
// 		_type(type)
// 		{}

// 	public:

// 		EntityIrId(EntityIrId&&) = default;
// 		EntityIrId(const EntityIrId&) = default;

// 		const auto& type() const { return _type; }
// 		const auto& index() const { return _index; }
		
// 		EntityIrId& operator=(EntityIrId&&) = default;
// 		EntityIrId& operator=(const EntityIrId&) = default;
// 		bool operator==(const EntityIrId&);
// 		// const EntityIr& operator*() const;
// 		// const EntityIr *operator->() const;
// 		friend std::ostream& operator<<(std::ostream& out, const EntityIrId& id);

// 		friend struct EntityIr;
// 	};
// };

// #endif
