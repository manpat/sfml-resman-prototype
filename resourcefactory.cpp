#include <iostream>

#include "resourcefactory.h"
#include "baseresource.h"

using namespace std;

std::map<string, ResourceFactory::AllocatorFunction> ResourceFactory::resourceAllocators = {};

class UnknownResource : public BaseResource {
public:
	UnknownResource()
		: BaseResource(){
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

baseresource_ptr ResourceFactory::createStub(const string& path, const string& type){
	L("ResourceFactory::createStub: ", type);

	if(resourceAllocators.find(type) != resourceAllocators.end()){
		auto r = resourceAllocators[type]();
		r->type = type;
		r->filePath = path;
		return r;
	}

	return new UnknownResource();
}