#include "resourcemanager.h"
#include "resourcebase.h"

std::map<string, ResourceBase*> ResourceManager::resourceMap = {};
std::queue<ResourceBase*> ResourceManager::loadQueue = {};

void ResourceManager::Update(){
	if(IsLoading()){
		auto r = loadQueue.front();
		r->LoadBase();
		loadQueue.pop();
	}
}

bool ResourceManager::IsLoading(){
	return !loadQueue.empty();
}

bool ResourceManager::IsResourceLoaded(string alias){
	return resourceMap.find(alias) != resourceMap.end();
}

void ResourceManager::LoadResource(string alias, string type, LoadMode lm){
	L("ResourceManager::LoadResource: ", alias);

	if(IsResourceLoaded(alias)) return;

	auto r = ResourceFactory::CreateStub(alias, type);
	if(lm == LoadMode::Block){
		r->LoadBase();
	}else if(lm == LoadMode::Queue){
		loadQueue.push(r);
	}

	resourceMap[alias] = r;
}