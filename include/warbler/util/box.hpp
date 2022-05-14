#ifndef WARBLER_UTIL_PTR_HPP
#define WARBLER_UTIL_PTR_HPP

namespace warbler
{
	template<typename T>
	class Box
	{
	private:

		T *_value;

	public:

		Box() :
		_value(nullptr)
		{}

		Box(T* value) :
		_value(value)
		{}

		Box(T&& value) :
		_value(new T(std::move(value)))
		{}

		Box(Box&& other) :
		_value(other._value)
		{
			other._value = nullptr;
		}

		Box(const Box&) = delete;

		~Box() { delete _value; }

		operator bool() const { return _value; }

		void fill(T *value)
		{
			if (_value)
			{
				delete _value;
			}

			_value = value;
		}

		T* operator->() { return _value; }
		const T* operator->() const { return _value; }
		
		T& operator*() { return *_value; }
		const T& operator*() const { return *_value; }

		Box& operator=(Box&& other) { new (this) auto(std::move(other)); return *this; }
		Box& operator=(T* ptr) { new (this) auto(ptr); return *this; }

		T* raw_ptr() { return _value; }
		const T* raw_ptr() const { return _value; }
	};
}

#endif
