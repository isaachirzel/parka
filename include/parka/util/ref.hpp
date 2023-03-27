#ifndef PARKA_UTIL_REF_HPP
#define PARKA_UTIL_REF_HPP

#include <cassert>

template <typename T>
class Ref
{
	T *_ptr;

public:

	Ref() :
	_ptr(nullptr)
	{}
	Ref(T& value) :
	_ptr(&value)
	{}
	Ref(Ref&&) = default;
	Ref(const Ref&) = default;
	~Ref() = default;

	operator bool() const { return _ptr; }
	bool hasValue() const { return _ptr; }
	T& value() { assert(_ptr); return _ptr; }
	const T& value() const { assert(_ptr); return _ptr; }
	T *operator ->() { assert(_ptr); return _ptr; }
	const T *operator ->() const { assert(_ptr); return _ptr; }
	T& operator *() { assert(_ptr); return _ptr; }
	const T& operator *() const { assert(_ptr); return _ptr; }
};

#endif
