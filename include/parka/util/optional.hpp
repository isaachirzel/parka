#ifndef PARKA_UTIL_RESULT_HPP
#define PARKA_UTIL_RESULT_HPP

#include <cassert>
#include <type_traits>
#include <utility>

template <typename T>
class Optional
{
private:

	union
	{
		T _value;
	};
	bool _hasValue;

public:

	Optional(T&& value) :
	_value(std::move(value)),
	_hasValue(true)
	{}

	template <typename U = T, typename = std::enable_if<std::is_fundamental_v<U>, U>>
	Optional(const T& value) :
	_value(value),
	_hasValue(true)
	{}

	Optional() :
	_hasValue(false)
	{}

	Optional(Optional&& other) :
	// _value(std::move(other._value)),
	_hasValue(other._hasValue)
	{
		if (other._hasValue)
		{
			T& newItem = _value;
			T& oldItem = other._value;

			new (&newItem) auto (std::move(oldItem));

			other._hasValue = false;
		}
	}

	Optional(const Optional&) = delete;

	~Optional()
	{
		if constexpr (!std::is_fundamental_v<T>)
		{
			if (_hasValue)
				_value.~T();
		}
	}

	Optional& operator =(Optional&& other)
	{
		new (this) auto(std::move(other));

		return *this;
	}

	Optional& operator =(const Optional& other) = delete;

	operator bool() const { return _hasValue; }
	bool hasValue() const { return _hasValue; }
	auto *operator->() { assert(_hasValue); return &_value; }
	const auto *operator->() const { assert(_hasValue); return &_value; }
	auto& operator*() { assert(_hasValue); return _value; }
	const auto& operator*() const { assert(_hasValue); return _value; }
	auto&& unwrap() { return std::move(_value); }
};

#endif
