#ifndef PARKA_UTIL_RESULT_HPP
#define PARKA_UTIL_RESULT_HPP

#include <cassert>
#include <utility>

template <typename T>
class Optional
{
private:
	bool _hasValue;
	union
	{
		T _value;
	};

public:

	Optional(T&& value) :
	_value(std::move(value)),
	_hasValue(true)
	{}

	Optional() :
	_hasValue(false)
	{}

	Optional(Optional&& other) :
	_hasValue(other._hasValue)
	{
		if (other._hasValue)
			new (&_value) auto (std::move(other._value));
	}

	Optional(const Optional&) = delete;

	~Optional()
	{
		if (_hasValue)
			_value.~T();
	}

	Optional& operator =(Optional&& other)
	{
		new (this) auto(std::move(other));

		return *this;
	}

	Optional& operator =(const Optional& other) = delete;

	operator bool() const { return _hasValue; }
	bool hasValue() const { return _hasValue; }
	auto& value() { assert(_hasValue); return _value; }
	const auto& value() const { assert(_hasValue); return _value; }
	auto&& unwrap() { return std::move(_value); }
};

#endif
