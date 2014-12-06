#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H
#include <functional>
#include <string>
#include <map>
#include "logger.h"
#include "resourceptr.h"

using std::string;

class BaseResource;

class ResourceAllocatorInterface {
public:
	virtual baseresource_ptr create() = 0;
};

template <class T>
class ResourceAllocatorImplementation : public ResourceAllocatorInterface{
public:
	baseresource_ptr create() override {
		return baseresource_ptr(new T);
	}
};

class ResourceFactory{
private:
	static std::map<string, ResourceAllocatorInterface*> resourceAllocators;
	static std::map<string, baseresource_ptr> errorResources;

public:
	template<typename T>
	static void addType();
	static baseresource_ptr createStub(const string& path, const string& type);
};

template<typename T>
void ResourceFactory::addType(){
	// resourceAllocators[T::Type()] = [](){
	// 	return baseresource_ptr(new T());
	// };
	resourceAllocators[T::Type()] = new ResourceAllocatorImplementation<T>;

	L("Resource type \"", T::Type(), "\" added");
}

#endif