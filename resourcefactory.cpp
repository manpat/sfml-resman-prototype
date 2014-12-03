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

	void Load() override {
		L("UnknownResource::Load ", path);
	}
	void Unload() override {
		L("UnknownResource::Unload ", path);
	}

	static string Type(){
		return "<unknown resource>";
	}
};

BaseResource* ResourceFactory::CreateStub(const string& path, const string& type){
	L("ResourceFactory::CreateStub: ", path, ' ', type);

	if(resourceAllocators.find(type) != resourceAllocators.end()){
		return resourceAllocators[type](path);
	}

	return new UnknownResource("");
}