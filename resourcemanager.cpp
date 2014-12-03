#include "resourcemanager.h"
#include "baseresource.h"

std::map<string, resource_ptr> ResourceManager::resourceMap = {};
std::queue<resource_ptr> ResourceManager::loadingQueue = {};
std::queue<resource_ptr> ResourceManager::unloadingQueue = {};
ResourceManager::LoadCompleteCallback ResourceManager::loadCompleteCallback = nullptr;

void ResourceManager::init(){
	throw("Not Implemented");
}
void ResourceManager::update(){
	if(isLoading()){
		auto r = loadingQueue.front();
		r->loadBase();
		loadingQueue.pop();
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
void ResourceManager::unload(string alias, UnloadMode um){
	throw("Not Implemented");
}
void ResourceManager::cleanupUnused(){
	throw("Not Implemented");
}
void ResourceManager::reload(string alias){
	throw("Not Implemented");
}


void ResourceManager::initPack(string path){
	throw("Not Implemented");
}
void ResourceManager::loadPack(string path, LoadMode lm){
	throw("Not Implemented");
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
	throw("Not Implemented");
	return 0;
}
size_t ResourceManager::getRAMUsage(){
	throw("Not Implemented");
	return 0;
}
size_t ResourceManager::getNumResources(){
	throw("Not Implemented");
	return 0;
}
std::list<resource_ptr> ResourceManager::listAll(){
	throw("Not Implemented");
	return std::list<resource_ptr>();
}
