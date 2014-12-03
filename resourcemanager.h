#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <functional>
#include <string>
#include <queue>
#include <list>
#include <map>

#include "resourcefactory.h"
#include "resourceptr.h"
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

private:
	static std::map<string, baseresource_ptr> resourceMap;
	static std::queue<baseresource_ptr> loadingQueue;
	static std::queue<baseresource_ptr> unloadingQueue;
	static LoadCompleteCallback loadCompleteCallback;

public:
	static void init();
	static void update();

	static void load(string path, string type, LoadMode = LoadMode::Queue);
	static void load(string path, string alias, string type, LoadMode = LoadMode::Queue);
	template<typename T> static resource_ptr<T> get(string alias);
	template<typename T> static resource_ptr<T> acquire(string alias, LoadMode = LoadMode::Queue);
	static void unload(string alias, UnloadMode = UnloadMode::Block);
	static void cleanupUnused();
	static void reload(string alias);

	static void initPack(string path);
	static void loadPack(string path, LoadMode = LoadMode::Queue);
	static void unloadPack(string path, UnloadMode = UnloadMode::Queue);
	static void reloadPack(string path);
	static void switchPacks(string path1, string path2);

	static bool isLoading();
	static bool isResourceLoaded(string alias);
	static size_t getNumToLoad();
	static size_t getRAMUsage();
	static size_t getNumResources();
	static std::list<baseresource_ptr> listAll();

	static void setLoadCompleteCallback(LoadCompleteCallback callback);
};

#include "resourcemanager.inl"

#endif