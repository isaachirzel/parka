#ifndef WARLER_UTIL_TABLE_HPP
#define WARLER_UTIL_TABLE_HPP

#include "parka/util/Common.hpp"
#include "parka/util/Pool.hpp"
#include <type_traits>

namespace parka
{
	namespace table
	{
		constexpr usize empty = -1;

		extern const usize primeNumbers[];
		extern const usize primeNumberCount;

		usize getCapacity(usize minimumCapacity);
	}

	template <typename Key, typename Value>
	class Table
	{
	public:

		class Item
		{
			Key _key;
			Value _value;
			usize _hash;

		public:

			Item(const Key& key, Value&& value, usize hash) :
			_key(key),
			_value(std::move(value)),
			_hash(hash)
			{}

			const auto& key() const { return _key; }
			const auto& value() const { return _value; }
			const auto& hash() const { return _hash; }

			auto& value() { return _value; }

			friend class Table;
		};

	private:

		Pool<usize> _slots;
		Pool<Item> _items;
		std::hash<Key> _hash;

	private:

		usize& getEmptySlot(const usize hash)
		{
			usize slotCount = _slots.count();
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

		usize getSlotIndex(const Key& key, const usize hash) const
		{
			usize slotCount = _slots.count();
			usize slotIndex = hash % _slots.count();
			usize step = 1;

			while (true)
			{
				auto& slot = _slots[slotIndex];

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

		void reserve(usize minimumCapacity)
		{
			if (_items.count() >= minimumCapacity)
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

		Table(usize minimumCapacity) :
		_slots(100'000), // TODO: Make this not just a static number
		_items(100'000)
		{
			auto capacity = table::getCapacity(minimumCapacity);

			_slots.reserve(capacity);
			_slots.fill(table::empty);
		}
		Table() : Table(table::primeNumbers[0]) {}
		Table(Table&&) = default;
		Table(const Table&) = delete;

		bool insert(const Key& key, const Value& value)
		{
			static_assert(std::is_copy_constructible_v<Value>, "Value must be copy constructible to pass const&");

			return insert(key, Value(value));
		}

		bool insert(const Key& key, Value&& value)
		{
			if (_items.count() * 2 >= _slots.count())
				reserve(_slots.count() * 2);

			auto hash = _hash(key);
			auto slotIndex = getSlotIndex(key, hash);
			auto& slot = _slots[slotIndex];
			
			if (slot != table::empty)
				return false;

			slot = _items.add(Item(key, std::move(value), hash));

			return true;
		}

		const Value *find(const Key& key) const
		{
			auto hash = _hash(key);
			auto slotIndex = getSlotIndex(key, hash);
			const auto& slot = _slots[slotIndex];

			if (slot == table::empty)
				return nullptr;

			const auto& item = _items[slot];

			return &item._value;
		}

		const auto *begin() const { return _items.begin(); }
		const auto *end() const { return _items.end(); }
		auto *begin() { return _items.begin(); }
		auto *end() { return _items.end(); }
		usize capacity() const { return _slots.count(); }
		usize count() const { return _items.count(); }
	};
}

#endif
