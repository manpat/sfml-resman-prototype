#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H
#include <functional>
#include <string>
#include <map>
#include "logger.h"
#include "resourceptr.h"

using std::string;

class BaseResource;

class ResourceFactory{
public:
	typedef std::function<resource_ptr ()> AllocatorFunction;

private:
	static std::map<string, AllocatorFunction> resourceAllocators;
	static std::map<string, resource_ptr> errorResources;

public:
	template<typename T>
	static void addType();
	static resource_ptr createStub(const string& path, const string& type);
};

template<typename T>
void ResourceFactory::addType(){
	resourceAllocators[T::Type()] = [](){
		return new T();
	};

	L("Resource type \"", T::Type(), "\" added");
}

#endif