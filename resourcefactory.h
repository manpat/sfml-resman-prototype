#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H
#include <functional>
#include <string>
#include <map>
#include "logger.h"

using std::string;

class BaseResource;

class ResourceFactory{
public:
	typedef std::function<BaseResource* (const string&)> AllocatorFunction;

private:
	static std::map<string, AllocatorFunction> resourceAllocators;
	static std::map<string, BaseResource*> errorResources;

public:
	template<typename T>
	static void addType();
	static BaseResource* createStub(const string& path, const string& type);
};

template<typename T>
void ResourceFactory::addType(){
	resourceAllocators[T::Type()] = [](const string& p){
		return new T(p);
	};

	L("Resource type \"", T::Type(), "\" added");
}

#endif