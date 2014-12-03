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
	typedef std::function<baseresource_ptr ()> AllocatorFunction;

private:
	static std::map<string, AllocatorFunction> resourceAllocators;
	static std::map<string, baseresource_ptr> errorResources;

public:
	template<typename T>
	static void addType();
	static baseresource_ptr createStub(const string& path, const string& type);
};

template<typename T>
void ResourceFactory::addType(){
	resourceAllocators[T::Type()] = [](){
		return baseresource_ptr(new T());
	};

	L("Resource type \"", T::Type(), "\" added");
}

#endif