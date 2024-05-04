#ifndef PARKA_UTIL_OPTIONAL_HPP
#define PARKA_UTIL_OPTIONAL_HPP

#include <type_traits>

namespace parka
{
	template <typename T>
	class Optional
	{
		alignas(T) char _value[sizeof(T)];
		bool _hasValue;

	public:

		Optional():
			_hasValue(false)
		{}

		template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
		Optional(const T *value):
			_hasValue(!!value)
		{
			if (!value)
				return;

			new (_value) T(*value);
		}

		Optional(T&& value):
			_hasValue(true)
		{
			new (_value) T(std::move((T&)value));
		}

		template <typename U = T, typename = std::enable_if<std::is_copy_constructible_v<U>, U>>
		Optional(const T& value):
			_hasValue(true)
		{
			new (_value) T(value);
		}

		Optional(Optional&& other):
			_hasValue(other._hasValue)
		{
			if (!other._hasValue)
				return;
			
			new (_value) T(std::move((T&)other._value));

			other._hasValue = false;
		}

		template <typename U = T, std::enable_if_t<std::is_copy_constructible_v<U>, bool> = true>
		Optional(const Optional& other):
			_hasValue(other._hasValue)
		{
			if (!other._hasValue)
				return;

			new (_value) T((const T&)other._value);
		}

		~Optional()
		{
			if constexpr (std::is_fundamental_v<T>)
			{
				if (_hasValue)
					((T&)_value).~T();
			}

			_hasValue = false;
		}

		Optional& operator=(Optional&& other)
		{
			if (_hasValue)
				((T&)_value).~T();

			if (other._hasValue)
				new (_value) T(std::move((T&)other._value));

			_hasValue = other._hasValue;

			return *this;
		}

		template <typename U = T, std::enable_if_t<std::is_copy_constructible_v<U>, bool> = true>
		Optional& operator=(const Optional& other)
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
		T& operator*() { assert(_hasValue); return (T&)_value; }
		const T& operator*() const { assert(_hasValue); return (const T&)_value; }
	};
}

#endif
