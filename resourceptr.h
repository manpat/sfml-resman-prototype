#ifndef RESOURCEPTR_H
#define RESOURCEPTR_H

#include <cstddef>

class BaseResource;

class resource_ptr{
public:
	struct PtrData{
		size_t count;
	};

protected:
	void _inc();
	void _dec();

protected:
	BaseResource* raw;
	PtrData* dat;

public:
	resource_ptr();
	resource_ptr(BaseResource* raw);
	resource_ptr(const resource_ptr& o);
	resource_ptr(resource_ptr&& o);
	~resource_ptr();

	resource_ptr& operator= (BaseResource* o);
	resource_ptr& operator= (resource_ptr& o);
	resource_ptr& operator= (resource_ptr&& o);

	BaseResource& operator*();
	BaseResource* operator->();

	BaseResource* getRaw();
	size_t getRefCount();
};

#endif