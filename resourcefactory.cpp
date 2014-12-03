#include <iostream>

#include "resourcefactory.h"
#include "baseresource.h"

using namespace std;

std::map<string, ResourceFactory::AllocatorFunction> ResourceFactory::resourceAllocators = {};

class UnknownResource : public BaseResource {
public:
	UnknownResource(const string&)
		: BaseResource(""){
		type = Type();
	}

	void load() override {
		L("UnknownResource::load ", filePath);
	}
	void unload() override {
		L("UnknownResource::unload ", filePath);
	}
	void reload() override {
		L("UnknownResource::reload ", filePath);
	}

	static string Type(){
		return "<unknown resource>";
	}
};

BaseResource* ResourceFactory::createStub(const string& path, const string& type){
	L("ResourceFactory::createStub: ", path, ' ', type);

	if(resourceAllocators.find(type) != resourceAllocators.end()){
		return resourceAllocators[type](path);
	}

	return new UnknownResource("");
}