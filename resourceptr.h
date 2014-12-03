#ifndef RESOURCEPTR_H
#define RESOURCEPTR_H

#include <cstddef>

class BaseResource;

struct PtrData{
	size_t count;
};

template<class T>
class resource_ptr{
	template<class D>
	friend class resource_ptr;
public:
	typedef resource_ptr<T> rp_t;

protected:
	void _inc();
	void _dec();

protected:
	T* raw;
	PtrData* dat;

public:
	resource_ptr();
	resource_ptr(T* raw);
	resource_ptr(const rp_t& o);
	resource_ptr(rp_t&& o);
	~resource_ptr();

	rp_t& operator= (T* o);
	rp_t& operator= (rp_t& o);
	rp_t& operator= (rp_t&& o);

	T& operator*();
	T* operator->();

	template<class D>
	resource_ptr<D> cast();

	operator bool();

	T* getRaw();
	size_t getRefCount();
};

typedef resource_ptr<BaseResource> baseresource_ptr;

#include "resourceptr.inl"

#endif