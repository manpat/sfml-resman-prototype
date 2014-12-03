#include "baseresource.h"

template<typename T>
resource_ptr<T> ResourceManager::get(string alias){
	baseresource_ptr r = nullptr;
	L("ResourceManager::get: ", alias);

	if(resourceMap.find(alias) == resourceMap.end()){
		throw("ResourceManager::get: Not done yet foo'");
	}else{
		r = resourceMap[alias];
		if(r->getType() != T::Type()){
			L("ResourceManager::get: Type mismatch between ", r->getType(), " and ", T::Type(), ", trying to acquire ", alias);
		}
	}

	return r.cast<T>();
}

template<typename T>
resource_ptr<T> ResourceManager::acquire(string alias, LoadMode lm){
	baseresource_ptr r = nullptr;
	L("ResourceManager::acquire: ", alias);

	if(resourceMap.find(alias) == resourceMap.end()){
		// TODO check if alias is actually filepath
		r = ResourceFactory::createStub(alias, T::Type());
		r->filePath = alias;
		r->alias = alias;

		if(lm == LoadMode::Block){
			r->loadBase();
		}else if(lm == LoadMode::Queue){
			loadingQueue.push(r);
		}

		resourceMap[alias] = r;
	}else{
		r = resourceMap[alias];
		if(r->getType() != T::Type()){
			L("ResourceManager::acquire: Type mismatch between ", r->getType(), " and ", T::Type(), ", trying to acquire ", alias);
		}
	}

	return r.cast<T>();
}