#ifndef WARBLER_UTIL_OPTIONAL_HPP
#define WARBLER_UTIL_OPTIONAL_HPP

namespace warbler
{
	template<typename T>
	class Optional
	{
	private:

		struct NullSpace {};
	
	private:

		union
		{
			NullSpace null;
			T _value;
		};

		bool _has_value;

	public:

		Optional() :
		_has_value(false)
		{}

		Optional(T&& value) :
		_value(std::move(value)),
		_has_value(true)
		{}

		Optional(Optional&& other) :
		_has_value(other._has_value)
		{
			if (_has_value)
				new (&_value) auto(std::move(other._value));
		}

		~Optional()
		{
			if (_has_value)
				_value.~T();
		}

		Optional& operator=(T&& other)
		{
			new(this) auto(std::move(other));
			return *this;
		}

		T& value() { assert(_has_value); return _value; }
		const T& value() const { return _value; }
		T& operator*() { return _value; }
		const T& operator*() const { return _value; }
		T* operator->() { return &_value; }
		const T* operator->() const { return &_value; }
		bool has_value() const { return _has_value; }
		operator bool() const { return _has_value; }
	};
}

#endif
