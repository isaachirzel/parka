#ifndef PARKA_UTIL_RESULT_HPP
#define PARKA_UTIL_RESULT_HPP

#include <type_traits>

namespace parka
{
	template <typename T>
	class Result
	{
		alignas(T) char _value[sizeof(T)];
		bool _hasValue;

	public:

		Result():
			_hasValue(false)
		{}

		template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
		Result(const T *value):
			_hasValue(!!value)
		{
			if (!value)
				return;

			new (_value) T(*value);
		}

		Result(T&& value):
			_hasValue(true)
		{
			new (_value) T(std::move((T&)value));
		}

		template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
		Result(const T& value):
			_hasValue(true)
		{
			new (_value) T(value);
		}

		Result(Result&& other):
			_hasValue(other._hasValue)
		{
			if (!other._hasValue)
				return;
			
			new (_value) T(std::move((T&)other._value));

			other._hasValue = false;
		}

		template <typename U = T, std::enable_if_t<std::is_copy_constructible_v<U>, bool> = true>
		Result(const Result& other):
			_hasValue(other._hasValue)
		{
			if (!other._hasValue)
				return;

			new (_value) T((const T&)other._value);
		}

		~Result()
		{
			if constexpr (!std::is_fundamental_v<T>)
			{
				if (_hasValue)
					((T&)_value).~T();
			}

			_hasValue = false;
		}

		Result& operator=(Result&& other)
		{
			if (_hasValue)
				((T&)_value).~T();

			if (other._hasValue)
				new (_value) T(std::move((T&)other._value));

			_hasValue = other._hasValue;

			return *this;
		}

		template <typename U = T, std::enable_if_t<std::is_copy_constructible_v<U>, bool> = true>
		Result& operator=(const Result& other)
		{
			if (_hasValue)
				((T&)_value).~T();

			if (other._hasValue)
				new (_value) T((const T&)other._value);

			_hasValue = other._hasValue;

			return *this;
		}

		operator bool() const { return _hasValue; }
		T *operator->() { assert(_hasValue); return (T*)_value; }
		const T *operator->() const { assert(_hasValue); return (const T*)_value; }
		T&& operator*() { assert(_hasValue); return std::move((T&)_value); }
		const T& operator*() const { assert(_hasValue); return (const T&)_value; }
	};
}

#endif
