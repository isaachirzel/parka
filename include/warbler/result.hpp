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
		ERROR_MEMORY,
		ERROR_ARGUMENT,
		ERROR_FILE,
		ERROR_PARSE,
		ERROR_NOT_FOUND,
		ERROR_INVALID_PTR,
		ERROR_NOT_IMPLEMENTED
	};

	struct NullSpace
	{
		int get() { return 0; }
	};

	static inline Error _not_implemented_error(const char *func_name)
	{
		fprintf(stderr, "\033[31mnot implemented:\033[0m %s()\n", func_name);
		return ERROR_NOT_IMPLEMENTED;
	}
	
	#define not_implemented_error() _not_implemented_error(__func__);
	#define try(expression) { Error error = expression; if (error) return error; }

	template<typename T>
	class Result
	{
	private:

		union
		{
			T _value;
			Error _error;
		};

		bool _ok;

	public:

		Result(T&& value) :
		_value(value),
		_ok(true)
		{}

		Result(Error error) :
		_error(error),
		_ok(false)
		{}

		Result(const Result& other) :
		_ok(other._ok)
		{
			if (_ok)
			{
				_value = other._value;
			}
			else
			{
				_error = other._error;
			}
		}

		Result(Result&& other) :
		_ok(other._ok)
		{
			if (_ok)
			{
				_value = std::move(other._value);
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
	};
}

#endif
