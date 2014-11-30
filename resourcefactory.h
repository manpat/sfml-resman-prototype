#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H
#include <functional>
#include <string>
#include <map>
#include "logger.h"

using std::string;

class ResourceBase;

class ResourceFactory{
public:
	typedef std::function<ResourceBase*(const string&)> LoaderFunction;

private:
	static std::map<string, LoaderFunction> resourceAllocators;

public:
	template<typename T>
	static void AddResourceType();
	static ResourceBase* CreateStub(const string& path, const string& type);
};

template<typename T>
void ResourceFactory::AddResourceType(){
	resourceAllocators[T::Type()] = [](const string& p){
		return new T(p);
	};

	L("Resource type \"", T::Type(), "\" added");
}

#endif