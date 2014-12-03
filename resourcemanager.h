
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <functional>
#include <string>
#include <queue>
#include <list>
#include <map>

#include "resourcefactory.h"
#include "resourcebase.h"
#include "logger.h"

using std::string;

class BaseResource;

enum class LoadMode {
	Queue,
	Block,
};
typedef LoadMode UnloadMode;
// enum class UnloadMode {
// 	Queue,
// 	Block,
// };

class ResourceManager {
public:
	typedef std::function<void()> LoadCompleteCallback;
	typedef BaseResource* ResourcePtr;

private:
	static std::map<string, ResourcePtr> resourceMap;
	static std::queue<ResourcePtr> loadingQueue;
	static std::queue<ResourcePtr> unloadingQueue;
	static LoadCompleteCallback loadCompleteCallback;

public:
	static void init();
	static void update();

	static void load(string alias, string type, LoadMode = LoadMode::Queue);
	template<typename T> static T* get(string alias);
	template<typename T> static T* acquire(string alias, LoadMode = LoadMode::Queue);
	static void unload(string alias, UnloadMode = UnloadMode::Block);
	static void cleanupUnused();
	static void reload(string alias);

	static void initPack(string path);
	static void loadPack(string path, LoadMode = LoadMode::Queue);
	static void unloadPack(string path, UnloadMode = UnloadMode::Queue);
	static void reloadPack(string path);
	static void switchPacks(string path1, string path2);

	static bool isLoading();
	static size_t getNumToLoad();
	static size_t getRAMUsage();
	static size_t getNumResources();
	static std::list<ResourcePtr> listAll();

	static void setLoadCompleteCallback(LoadCompleteCallback callback);
};

template<typename T>
T* ResourceManager::AcquireResource(string alias, LoadMode lm){
	ResourcePtr r = nullptr;
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