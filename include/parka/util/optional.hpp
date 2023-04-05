#ifndef PARKA_UTIL_RESULT_HPP
#define PARKA_UTIL_RESULT_HPP

#include <cassert>
#include <type_traits>

template <typename T>
class Optional
{
	alignas(T) char _value[sizeof(T)];
	bool _hasValue;

public:

	Optional() :
	_hasValue(false)
	{}

	Optional(T&& value) :
	_hasValue(true)
	{
		new ((T*)_value) auto (std::move(value));
	}

	template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
	Optional(const T& value) :
	_hasValue(true)
	{
		new ((T*)_value) auto (value);
	}

	Optional(Optional&& other) :
	_hasValue(other._hasValue)
	{
		if (other._hasValue)
		{
			auto *newItem = (T*)_value;
			auto *oldItem = (T*)other._value;

			new (newItem) auto (std::move(*oldItem));

			other._hasValue = false;
		}
	}

	template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
	Optional(const Optional& other)
	{
		new (this) auto(other);
	}

	~Optional()
	{
		if constexpr (!std::is_fundamental_v<T>)
		{
			if (_hasValue)
				((T&)_value).~T();

			_hasValue = false;
		}
	}

	Optional& operator =(Optional&& other)
	{
		new (this) auto(std::move(other));

		return *this;
	}

	template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
	Optional& operator =(const Optional& other)
	{
		new (this) auto (other);
		return *this;
	}

	operator bool() const { return _hasValue; }
	const bool& hasValue() const { return _hasValue; }
	T *operator->() { assert(_hasValue); return (T*)_value; }
	const T *operator->() const { assert(_hasValue); return (T*)_value; }
	T&& operator*() { assert(_hasValue); return std::move((T&)_value); }
	const T& operator*() const { assert(_hasValue); return (T&)_value; }
};

#endif
