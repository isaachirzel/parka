#ifndef PARKA_UTIL_ARRAY_HPP
#define PARKA_UTIL_ARRAY_HPP

#include "parka/util/primitives.hpp"

#include <cassert>
#include <initializer_list>
#include <iostream>
#include <new>
#include <stdexcept>

#include <cstdlib>
#include <type_traits>

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
	_data((T*)malloc(sizeof(T) * capacity))
	{
		if (!_data)
			throw std::bad_alloc();
	}
	Array(Array&& other) :
	_length(other._length),
	_capacity(other._capacity),
	_data(other._data)
	{
		other._data = nullptr;
		other._capacity = 0;
		other._length = 0;
	}
	Array(const Array&) = delete;
	~Array()
	{
		for (usize i = 0; i < _length; ++i)
			_data[i].~T();
		
		free(_data);
	}

	void reserve(usize minimum)
	{
		if (_capacity >= minimum)
			return;

		auto *newData = (T*)realloc(_data, sizeof(T) * minimum);

		if (!newData)
			throw std::bad_alloc();

		_data = newData;
		_capacity = minimum;
	}

	T& push(T&& value)
	{
		reserve(_length + 1);
		
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
		if (_length > 0)
		{
			_data[_length  - 1].~T();
			_length -= 1;
		}
	}

	void clear()
	{
		for (usize i = 0; i < _length; ++i)
			_data[i].~T();

		_length = 0;
	}

	T& operator[](usize index)
	{
		assert(index < _length);
		return _data[index];
	}

	const T& operator[](usize index) const
	{
		assert(index < _length);
		return _data[index];
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

#endif
