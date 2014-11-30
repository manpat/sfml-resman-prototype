
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <queue>
#include <map>

#include "resourcefactory.h"
#include "resourcebase.h"
#include "logger.h"

using std::string;

class ResourceBase;

enum class LoadMode {
	Queue,
	Block,
};

class ResourceManager {
private:
	static std::map<string, ResourceBase*> resourceMap;
	static std::queue<ResourceBase*> loadQueue;

public:
	static void LoadResource(string alias, string type, LoadMode = LoadMode::Queue);

	template<typename T>
	static T* GetResource(string alias);

	template<typename T>
	static T* AcquireResource(string alias, LoadMode = LoadMode::Queue);

	static bool IsResourceLoaded(string alias);

	static void Update();
	static bool IsLoading();
};

template<typename T>
T* ResourceManager::AcquireResource(string alias, LoadMode lm){
	ResourceBase* r = nullptr;
	L("ResourceManager::AcquireResource: ", alias);

	if(resourceMap.find(alias) == resourceMap.end()){
		r = ResourceFactory::CreateStub(alias, T::Type());

		if(lm == LoadMode::Block){
			r->LoadBase();
		}else if(lm == LoadMode::Queue){
			loadQueue.push(r);
		}

		resourceMap[alias] = r;
	}else{
		r = resourceMap[alias];
		if(r->GetType() != T::Type()){
			L("ResourceManager::AcquireResource: Type mismatch between ", r->GetType(), " and ", T::Type(), ", trying to acquire ", alias);
		}
	}

	return static_cast<T*>(r);
}


#endif