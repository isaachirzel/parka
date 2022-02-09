#ifndef WARBLER_UTIL_PTR_HPP
#define WARBLER_UTIL_PTR_HPP

namespace warbler
{
	template<typename T>
	class Ptr
	{
	private:

		T *_value;

	public:

		Ptr(T* value) :
		_value(value)
		{}

		Ptr(T&& value) :
		_value(new T(std::move(value)))
		{}

		Ptr(Ptr&& other) :
		_value(other._value)
		{
			other._value = nullptr;
		}

		Ptr(const Ptr&) = delete;

		~Ptr() { delete _value; }

		T* operator->() { return _value; }
		T& operator*() { return *_value; }
	};
}

#endif
