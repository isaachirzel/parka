#ifndef PARKA_UTIL_FLAT_MAP_HPP
#define PARKA_UTIL_FLAT_MAP_HPP

#include "parka/util/Common.hpp"
#include "parka/util/TableUtil.hpp"
#include <cstring>
#include <stdexcept>

namespace parka
{
	template <typename Key, typename Value>
	class FlatMap
	{
		class Item
		{
			Key _key;
			alignas(Value) char _value[sizeof(Value)];
			usize _hash;
			bool _hasValue;
			bool _isDeleted;

		public:

			Item():
				_key(),
				_value(),
				_hash(0),
				_hasValue(false),
				_isDeleted(false)
			{
				std::memset(_value, 0, sizeof(Value));
			}
			Item(const Key& key, Value&& value, usize hash):
				_key(key),
				_value(),
				_hash(hash),
				_hasValue(true),
				_isDeleted(false)
			{
				new (_value) Value(std::move(value));
			}
			Item(Item&&) = delete;
			Item(const Item&) = delete;
			~Item()
			{
				if (_hasValue)
					((Value*)_value)->~Value();
			}

			const auto& key() const { return _key; }
			const auto& value() const { return _value; }
			const auto& hash() const { return _hash; }
			const auto& hasValue() const { return _hasValue; }
			const auto& isDeleted() const { return _isDeleted; }

			auto& value() { return _value; }

			Item& operator=(Item&& other)
			{
				if (_hasValue)
					((Value&)_value).~Value();

				_key = std::move(other._key);
				_hash = other._hash;
				_hasValue = other._hasValue;
				_isDeleted = other._isDeleted;

				if (other._hasValue)
				{
					new (_value) Value(std::move((Value&)other._value));

					other._hasValue = false;
				}

				return *this;
			}

			friend class FlatMap;
		};

		class Insertion
		{
			Value& _ref;
			bool _success;

		private:

			Insertion(Value& ref, bool success):
				_ref(ref),
				_success(success)
			{}

		public:
		
			Insertion(Insertion&&) = default;
			Insertion(const Insertion&) = default;

			operator bool() const { return _success; }
			Value& operator*() { return _ref; }
			const Value& operator*() const { return _ref; }
			Value* operator->() { return &_ref; }
			const Value* operator->() const { return &_ref; }

			friend class FlatMap;
		};

	private:

		Item* _items;
		std::hash<Key> _hash;
		usize _capacity;
		usize _count;

	private:

		Item& getEmptyItem(const usize hash)
		{
			usize index = hash % _capacity;
			usize step = 1;

			while (true)
			{
				auto& item = _items[index];

				if (!item._hasValue)
					return item;

				index = (hash + step) % _capacity;
				step <<= 1;
			}
		}

		Item& getItem(const Key& key, const usize hash)
		{
			usize index = hash % _capacity;
			usize step = 1;

			while (true)
			{
				auto& item = _items[index];

				if (!item._hasValue || (item._hash == hash && item._key == key))
					return item;
				
				index = (hash + step) % _capacity;
				step <<= 1;
			}
		}

		Item& getItem(const Key& key)
		{
			const auto hash = _hash(key);

			return getItem(key, hash);
		}

	public:

		FlatMap():
			_items(nullptr),
			_hash(),
			_capacity(0),
			_count(0)
		{}
		FlatMap(usize count):
			FlatMap()
		{
			reserve(count);
		}
		FlatMap(FlatMap&&) = default;
		FlatMap(const FlatMap&) = delete;

		void reserve(usize count)
		{
			const auto minimumCapacity = count * 2;

			if (_capacity >= minimumCapacity)
				return;


			auto oldCapacity = _capacity;
			auto* oldItems = _items;
			auto newCapacity = table::getCapacity(minimumCapacity);
			auto* newItems = new Item[newCapacity];	

			_items = newItems;
			_capacity = newCapacity;

			for (usize i = 0; i < oldCapacity; ++i)
			{
				auto& oldItem = oldItems[i];

				if (!oldItem._hasValue)
					continue;

				auto& newItem = getEmptyItem(oldItem._hash);

				newItem = std::move(oldItem);
			}
		}

		Insertion insert(const Key& key, Value&& value)
		{
			const usize newCount = _count + 1;

			reserve(newCount);

			const auto hash = _hash(key);
			auto& item = getItem(key, hash);
			auto success = false;

			if (!item._hasValue)
			{
				success = true;
				item = Item(key, std::move(value), hash);
			}

			_count = newCount;

			return Insertion((Value&)item._value, success);
		}

		template <typename U = Value, typename = std::enable_if_t<std::is_copy_constructible_v<U>>>
		Insertion insert(const Key& key, const Value& value)
		{
			return insert(key, Value(value));
		}

		Value *find(const Key& key)
		{
			if (_count == 0)
				return nullptr;

			auto& item = getItem(key);
			
			if (!item._hasValue)
				return nullptr;
			
			return (Value*)item._value;
		}

		const Value *find(const Key& key) const
		{
			return const_cast<FlatMap*>(this)->find(key);
		}

		Value& get(const Key& key)
		{
			if (_count == 0)
				throw std::runtime_error("FlatMap is empty.");

			auto& item = getItem(key);
			
			if (!item._hasValue)
				throw std::runtime_error("Unable to find value.");
			
			return (Value&)item._value;
		}

		const Value& get(const Key& key) const
		{
			return const_cast<FlatMap*>(this)->get(key);
		}

		const auto& capacity() const { return _capacity; }
		const auto& count() const { return _count; }
	};
}

#endif
