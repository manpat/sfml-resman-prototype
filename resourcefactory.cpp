#include <iostream>

#include "resourcefactory.h"
#include "resourcebase.h"

using namespace std;

std::map<string, ResourceFactory::LoaderFunction> ResourceFactory::resourceAllocators = {};

class UnknownResource : public ResourceBase {
public:
	UnknownResource(const string&)
		: ResourceBase(""){
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

ResourceBase* ResourceFactory::CreateStub(const string& path, const string& type){
	L("ResourceFactory::CreateStub: ", path, ' ', type);

	if(resourceAllocators.find(type) != resourceAllocators.end()){
		return resourceAllocators[type](path);
	}

	return new UnknownResource("");
}