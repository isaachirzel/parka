#ifndef PARKA_UTIL_SET_HPP
#define PARKA_UTIL_SET_HPP

#include "parka/util/Array.hpp"
#include "parka/util/BigArray.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/TableUtil.hpp"

namespace parka
{
	template <typename T>
	class Set
	{
		class Item
		{
			T _key;
			u64 _hash;

		public:

			Item(T&& key, u64 hash):
				_key(std::move(key)),
				_hash(hash)
			{}
			Item(Item&&) = default;
			Item(const Item&) = delete;

			const auto& key() const { return _key; }
			const auto& hash() const { return _hash; }

			auto& key() { return _key; }

			friend class Set;
		};

	private:

		BigArray<Item> _items;
		Pool<usize> _slots;
		std::hash<T> _hash;

	private:

		usize& getEmptySlot(const usize hash)
		{
			usize slotCount = _slots.length();
			usize slotIndex = hash % slotCount;
			usize step = 1;

			while (true)
			{
				auto& slot = _slots[slotIndex];

				if (slot == table::empty)
					return slot;

				slotIndex = (hash + step) % slotCount;
				step <<= 1;
			}
		}

		usize getSlotIndex(const T& key, const usize hash) const
		{
			const usize slotCount = _slots.length();
			usize slotIndex = hash % slotCount;
			usize step = 1;

			while (true)
			{
				const auto slot = _slots[slotIndex];

				if (slot == table::empty)
					break;

				auto& item = _items[slot];

				if (hash == item._hash && key == item._key)
					break;
				
				slotIndex = (hash + step) % slotCount;
				step <<= 1;
			}

			return slotIndex;
		}

		usize getSlot(const T& key) const
		{
			auto hash = _hash(key);
			auto slotIndex = getSlotIndex(key, hash);
			auto slot = _slots[slotIndex];

			return slot;
		}

		void reserve(usize minimumCapacity)
		{
			if (_items.length() >= minimumCapacity)
				return;

			auto newCapacity = table::getCapacity(minimumCapacity);
			
			_slots.reserve(newCapacity);
			_slots.fill(table::empty);

			usize index = 0;

			for (const auto& item : _items)
			{
				auto& slot = getEmptySlot(item._hash);

				slot = index;
				index += 1;
			}
		}

	public:

		Set(usize minimumCapacity, usize maxCount):
			_items(maxCount),
			_slots(maxCount * 2)
		{
			auto capacity = table::getCapacity(minimumCapacity);

			_slots.reserve(capacity);
			_slots.fill(table::empty);
		}
		Set(Set&&) = default;
		Set(const Set&) = delete;

		template <typename U = T, typename = std::enable_if_t<std::is_copy_constructible_v<U>>>
		T& insert(const T& key)
		{
			return insert(T(key));
		}

		T& insert(T&& key)
		{
			if (_slots.length() < _items.length() * 2)
				reserve(_slots.length() * 2);

			auto hash = _hash(key);
			auto slotIndex = getSlotIndex(key, hash);
			auto& slot = _slots[slotIndex];
		
			if (slot == table::empty)	
			{
				slot = _items.length();
				
				_items.push(Item(std::move(key), hash));
			}

			return _items[slot].key();
		}

		T *find(const T& key)
		{
			auto slot = getSlot(key);

			if (slot == table::empty)
				return nullptr;

			auto& item = _items[slot];

			return &item._value;
		}

		const T *find(const T& key) const
		{
			auto slot = getSlot(key);

			if (slot == table::empty)
				return nullptr;

			auto& item = _items[slot];

			return &item._value;
		}

		T& get(const T& key)
		{
			auto slot = getSlot(key);

			assert(slot != table::empty);

			auto& item = _items[slot];

			return item._value;
		}

		const T& get(const T& key) const
		{
			auto slot = getSlot(key);

			assert(slot != table::empty);

			auto& item = _items[slot];

			return item._value;
		}

		const auto *begin() const { return _items.begin(); }
		const auto *end() const { return _items.end(); }
		auto *begin() { return _items.begin(); }
		auto *end() { return _items.end(); }
		usize capacity() const { return _slots.length(); }
		usize count() const { return _items.length(); }
	};
}

#endif
