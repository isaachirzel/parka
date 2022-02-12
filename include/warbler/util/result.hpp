#ifndef WARBLER_RESULT_HPP
#define WARBLER_RESULT_HPP

// standard headers
#include <cstdio>
#include <utility>
#include <cassert>

namespace warbler
{
	enum Error
	{
		ERROR_MEMORY = 1,
		ERROR_ARGUMENT,
		ERROR_FILE,
		ERROR_PARSE,
		ERROR_NOT_FOUND,
		ERROR_INVALID_PTR,
		ERROR_NOT_IMPLEMENTED,
		ERROR_VALIDATE
	};

	template<typename T>
	class Result
	{
	private:

		struct NullSpace {};

	private:

		union
		{
			NullSpace _null;
			T _value;
		};

		bool _ok;

	public:

		Result() :
		_ok(false)
		{}

		Result(T&& value) :
		_value(std::move(value)),
		_ok(true)
		{}

		Result(Result&& other) :
		_ok(other._ok)
		{
			if (_ok)
			{
				new(&_value) auto(std::move(other._value));
				other._ok = false;
			}
			else
			{
				_error = other._error;
			}

		}

		~Result()
		{
			if (_ok)
				_value.~T();
		}

		T&& unwrap() { assert(_ok); return std::move(_value); }
		Error error() const { assert(!_ok); return _error; }
		bool has_error() const { return !_ok; }
		bool is_ok() const { return _ok; }
		operator Error() const { assert(!_ok); return _error; }
		operator bool() const { return _ok; }
		operator int() const { return _ok ? 0 : (int)_error; }
	};
}

#endif
