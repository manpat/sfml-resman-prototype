#include "baseresource.h"

template<typename T>
T* ResourceManager::get(string alias){
	ResourcePtr r = nullptr;
	L("ResourceManager::get: ", alias);

	if(resourceMap.find(alias) == resourceMap.end()){
		// r = ResourceFactory::CreateStub(alias, T::Type());

		// if(lm == LoadMode::Block){
		// 	r->LoadBase();
		// }else if(lm == LoadMode::Queue){
		// 	loadQueue.push(r);
		// }

		// resourceMap[alias] = r;
		throw("Not done yet foo'");
	}else{
		r = resourceMap[alias];
		if(r->getType() != T::Type()){
			L("ResourceManager::get: Type mismatch between ", r->getType(), " and ", T::Type(), ", trying to acquire ", alias);
		}
	}

	return static_cast<T*>(r);
}

template<typename T>
T* ResourceManager::acquire(string alias, LoadMode lm){
	ResourcePtr r = nullptr;
	L("ResourceManager::acquire: ", alias);

	if(resourceMap.find(alias) == resourceMap.end()){
		r = ResourceFactory::createStub(alias, T::Type());

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

	return static_cast<T*>(r);
}