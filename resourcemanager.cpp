#include "resourcemanager.h"
#include "baseresource.h"
#include "luaparser.h"

std::map<string, baseresource_ptr> ResourceManager::resourceMap = {};
std::queue<baseresource_ptr> ResourceManager::loadingQueue = {};
std::queue<baseresource_ptr> ResourceManager::unloadingQueue = {};
ResourceManager::LoadCompleteCallback ResourceManager::loadCompleteCallback = nullptr;

void ResourceManager::init(){
	throw("Not Implemented");
}
void ResourceManager::update(){
	if(isLoading()){
		auto r = loadingQueue.front();
		r->loadBase();
		loadingQueue.pop();
		if(loadingQueue.empty() && loadCompleteCallback) 
			loadCompleteCallback();
	}

	if(!unloadingQueue.empty()){
		auto r = unloadingQueue.front();
		r->unloadBase();
		unloadingQueue.pop();
	}
}
void ResourceManager::load(string path, string type, LoadMode lm){
	L("ResourceManager::load: ", path);

	if(isResourceLoaded(path)) return;

	auto r = ResourceFactory::createStub(path, type);
	r->alias = path;

	if(lm == LoadMode::Block){
		r->loadBase();
	}else if(lm == LoadMode::Queue){
		loadingQueue.push(r);
	}

	resourceMap[path] = r; // treat path as alias
}
void ResourceManager::load(string path, string alias, string type, LoadMode lm){
	L("ResourceManager::load: ", path);

	if(isResourceLoaded(path)) return;

	auto r = ResourceFactory::createStub(path, type);
	r->alias = alias;

	if(lm == LoadMode::Block){
		r->loadBase();
	}else if(lm == LoadMode::Queue){
		loadingQueue.push(r);
	}

	resourceMap[alias] = r;
}
void ResourceManager::unload(string alias, UnloadMode um){
	L("ResourceManager::unload: ", alias);
	if(!isResourceLoaded(alias)) return;

	auto r = resourceMap[alias];
	if(!r->isLoaded()) return;

	if(um == UnloadMode::Block){
		r->unloadBase();
	}else if(um == UnloadMode::Queue){
		unloadingQueue.push(r);
	}
}
void ResourceManager::cleanupUnused(){
	for(auto& arp : resourceMap){
		auto& r = arp.second;
		if(r.getRefCount() == 1)
			r->unloadBase();
	}
}
void ResourceManager::reload(string alias){
	throw("Not Implemented");
}


void ResourceManager::initPack(string path){
	throw("Not Implemented");
}
void ResourceManager::loadPack(string path, LoadMode lm){
	auto rs = LuaParser::parsePack(path);
	for(auto r : rs){
		L("\t", r.path);
		load(r.path, r.alias, r.type, lm);
	}
}
void ResourceManager::unloadPack(string path, UnloadMode um){
	throw("Not Implemented");
}
void ResourceManager::reloadPack(string path){
	throw("Not Implemented");
}
void ResourceManager::switchPacks(string path, string path2){
	throw("Not Implemented");
}


bool ResourceManager::isLoading(){
	return !loadingQueue.empty();
}
bool ResourceManager::isResourceLoaded(string alias){
	return resourceMap.find(alias) != resourceMap.end();
}
size_t ResourceManager::getNumToLoad(){
	return loadingQueue.size();
}
size_t ResourceManager::getRAMUsage(){
	throw("Not Implemented");
	return 0;
}
size_t ResourceManager::getNumResources(){
	return resourceMap.size();
}
std::list<baseresource_ptr> ResourceManager::listAll(){
	std::list<baseresource_ptr> l;

	for(auto arp : resourceMap){
		l.push_back(arp.second);
	}

	return l;
}

void ResourceManager::setLoadCompleteCallback(LoadCompleteCallback callback){
	loadCompleteCallback = callback;
}
