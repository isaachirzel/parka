#ifndef PARKA_UTIL_BOX_HPP
#define PARKA_UTIL_BOX_HPP

#include <utility>
#include <cassert>

template <typename T>
class Box
{
	T *_ptr;

public:

	Box(T&& value) :
	_ptr(new T(std::move(value)))
	{}
	Box(T *ptr) :
	_ptr(ptr)
	{
		assert(_ptr != nullptr);
	}
	Box(Box&& other)
	{
		_ptr = other._ptr;
		other._ptr = nullptr;
	}
	Box(const Box&) = delete;
	~Box() { delete _ptr; }

	Box& operator=(Box&& other)
	{
		new (this) auto(std::move(other));

		return *this;
	}

	T *operator ->() { return _ptr; }
	const T *operator ->() const { return _ptr; }
	T& operator *() { return _ptr; }
	const T& operator *() const { return _ptr; }
};

#endif
