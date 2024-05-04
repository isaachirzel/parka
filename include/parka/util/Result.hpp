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
			if (value)
				new (_value) auto (*value);
		}

		Result(T&& value):
		_hasValue(true)
		{
			new ((T*)_value) auto (std::move(value));
		}

		template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
		Result(const T& value):
		_hasValue(true)
		{
			new ((T*)_value) auto (value);
		}

		Result(Result&& other):
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

		template <typename U = T, std::enable_if_t<std::is_copy_constructible_v<U>, bool> = true>
		Result(const Result& other):
		_hasValue(other._value)
		{
			if (_hasValue)
				_value = other._value;
		}

		~Result()
		{
			if constexpr (!std::is_fundamental_v<T>)
			{
				if (_hasValue)
					((T&)_value).~T();

				_hasValue = false;
			}
		}

		Result& operator=(Result&& other)
		{
			new (this) auto(std::move(other));

			return *this;
		}

		// template <typename U = T, typename = std::enable_if_t<std::is_copy_constructible_v<U>>>
		template <typename U = T, std::enable_if_t<std::is_copy_constructible_v<U>, bool> = true>
		Result& operator=(const Result& other)
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
}

#endif
