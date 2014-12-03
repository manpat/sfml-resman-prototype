#include "resourcemanager.h"
#include "baseresource.h"

std::map<string, ResourceManager::ResourcePtr> ResourceManager::resourceMap = {};
std::queue<ResourceManager::ResourcePtr> ResourceManager::loadingQueue = {};
std::queue<ResourceManager::ResourcePtr> ResourceManager::unloadingQueue = {};
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
void ResourceManager::load(string alias, string type, LoadMode lm){
	L("ResourceManager::load: ", alias);

	if(isResourceLoaded(alias)) return;

	auto r = ResourceFactory::createStub(alias, type);
	if(lm == LoadMode::Block){
		r->loadBase();
	}else if(lm == LoadMode::Queue){
		loadingQueue.push(r);
	}

	resourceMap[alias] = r;
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
auto ResourceManager::listAll() -> std::list<ResourcePtr> {
	throw("Not Implemented");
	return std::list<ResourcePtr>();
}
