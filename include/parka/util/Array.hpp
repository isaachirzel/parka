#ifndef PARKA_UTIL_ARRAY_HPP
#define PARKA_UTIL_ARRAY_HPP

#include "parka/util/Common.hpp"

#include <cassert>
#include <stdexcept>
#include <cstdlib>
#include <type_traits>

namespace parka
{
	template <typename T>
	class Array
	{
		usize _length;
		usize _capacity;
		T *_data;

	public:

		Array() :
		_length(0),
		_capacity(0),
		_data(nullptr)
		{}
		Array(usize capacity) :
		_length(0),
		_capacity(capacity),
		_data((T*)::operator new(sizeof(T) * capacity))
		{
			if (!_data)
				throw std::bad_alloc();
		}
		Array(Array&& other) :
		_length(other._length),
		_capacity(other._capacity),
		_data(other._data)
		{
			other._length = 0;
			other._capacity = 0;
			other._data = nullptr;
		}
		Array(const Array&) = delete;
		~Array()
		{
			if constexpr (!std::is_trivially_destructible_v<T>)
			{
				for (usize i = 0; i < _length; ++i)
					_data[i].~T();
			}
			
			::operator delete(_data);
		}

		void reserve(usize minimum)
		{
			if (_capacity >= minimum)
				return;

			usize newCapacity = minimum * 1.5;
			auto *oldData = _data;
			auto *newData = (T*)::operator new( sizeof(T) * newCapacity);

			if (newData == nullptr)
				throw std::bad_alloc();

			for (usize i = 0; i < _length; ++i)
			{
				T& oldItem = oldData[i];
				T& newItem = newData[i];

				new (&newItem) auto (std::move(oldItem));
			}

			::operator delete(oldData);
			
			_data = newData;
			_capacity = newCapacity;
		}

		template <typename U = T, typename = std::enable_if_t<std::is_fundamental_v<U>>>
		T& push(const T& value)
		{
			if (_length >= _capacity)
				reserve(_length + 4);
			
			T& ref = _data[_length];

			ref = value;
			_length += 1;

			return ref;
		}

		T& push(T&& value)
		{
			if (_length >= _capacity)
				reserve(_length + 4);
			
			T& ref = _data[_length];

			new (&ref) auto(std::move(value));

			_length += 1;

			return ref;
		}

		Array& concat(Array& other)
		{
			reserve(_length + other._length);

			for (usize i = 0; i < other.length(); ++i)
			{
				new (&_data[_length + i]) auto (std::move(other[i]));
			}
			
			_length += other._length;
			other._length = 0;

			return *this;
		}

		T& push(T& value)
		{
			return push(std::move(value));
		}

		void pop()
		{
			assert(_length > 0);
			
			_data[_length  - 1].~T();
			_length -= 1;
		}

		void clear()
		{
			for (usize i = 0; i < _length; ++i)
				_data[i].~T();

			_length = 0;
		}

		constexpr T& operator[](usize index)
		{
			assert(index < _length);
			return _data[index];
		}

		constexpr const T& operator[](usize index) const
		{
			assert(index < _length);
			return _data[index];
		}

		usize getIndex(const T *ptr) const
		{
			assert(ptr > _data);
			assert(ptr - _data < (isize)_length);
			return ptr - _data;
		}
		
		T& back() { assert(_length > 0); return _data[_length - 1]; }
		T& front() { assert(_length > 0); return _data[0]; }
		T* begin() { return &_data[0]; }
		T* end() { return &_data[_length]; }
		const T* begin() const { return &_data[0]; }
		const T* end() const { return &_data[_length]; }

		const auto& length() const { return _length; }
		const auto& capacity() const { return _capacity; }
	};
}

#endif
