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
		ERROR_NONE,
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
			NullSpace _null;
			T _value;
		};

		Error _error;

	public:

		Result(T&& value) :
		_value(value),
		_error(ERROR_NONE)
		{}

		Result(Error error) :
		_null(),
		_error(error)
		{}

		Result(const Result& other) :
		_error(other.error())
		{
			if (_error == ERROR_NONE)
			{
				_value = other.value();
			}
			else
			{
				_null = {};
			}
		}

		Result(Result&& other) :
		_error(other._error)
		{
			if (_error == ERROR_NONE)
			{
				_value = std::move(other._value);
			}
			else
			{
				_null = {};
			}
		}

		~Result()
		{
			if (_error = ERROR_NONE)
				_value.~T();
		}

		T&& unwrap() { assert(_error == ERROR_NONE); return std::move(_value); }
		T value() const { return _value; }
		Error error() const { return _error; }
		bool has_error() const { return _error; }
		bool is_ok() const { return _error == ERROR_NONE; }
	};
}

#endif
