#ifndef WARBLER_RESULT_HPP
#define WARBLER_RESULT_HPP

// standard headers
#include <cstdio>
#include <utility>
#include <cassert>

namespace warbler
{
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

		}

		~Result()
		{
			if (_ok)
				_value.~T();
		}

		T&& unwrap() { assert(_ok); return std::move(_value); }
		bool is_ok() const { return _ok; }
		operator bool() const { return _ok; }
	};
}

#endif
