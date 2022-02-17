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

		Ptr() :
		_value(nullptr)
		{}

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

		operator bool() const { return _value; }

		T* operator->() { return _value; }
		const T* operator->() const { return _value; }
		
		T& operator*() { return *_value; }
		const T& operator*() const { return *_value; }

		Ptr& operator=(Ptr&& other) { new (this) auto(std::move(other)); return *this; }

		T* raw_ptr() { return _value; }
		const T* raw_ptr() const { return _value; }
	};
}

#endif
