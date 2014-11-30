#include <iostream>
#include <vector>
#include "resourcemanager.h"
#include "resourcebase.h"

#include "logger.h"

using namespace std;

class File : public ResourceBase {
public:
	File(const string& path) 
		: ResourceBase(path){

		type = Type();
	}

	void Load() override {
		L("File::Load ", path);
	}
	void Unload() override {
		L("File::Unload ", path);
	}

	static string Type(){
		return "file";
	}
};

class Sound : public ResourceBase {
public:
	Sound(const string& p)
		: ResourceBase(p){
		type = Type();
	}

	void Load() override {
		L("Sound::Load ", path);
	}
	void Unload() override {
		L("Sound::Unload ", path);
	}

	static string Type(){
		return "sound";
	}
};

int main(){
	try{
		InitLogFile("log.txt");

		L("Things");

		L("\n--- Adding Resource Types ---");

		// Create class generating stubs
		ResourceFactory::AddResourceType<File>();
		ResourceFactory::AddResourceType<Sound>();

		L("\n--- Acquiring Resources ---");

		// These resources haven't been loaded yet so 
		//	AcquireResource queues loading.
		ResourceManager::AcquireResource<File>("file1.txt");
		ResourceManager::LoadResource("file2.jpg", File::Type(), LoadMode::Block);
		auto s = ResourceManager::AcquireResource<Sound>("file3.lol");

		L("\n--- Beginning update loop ---");

		// Waits until everything is loaded
		while(ResourceManager::IsLoading())
		// while(!s->IsLoaded())
			ResourceManager::Update();

		L("\n--- Acquiring Resources Again ---");

		// All resources will now be loaded
		ResourceManager::AcquireResource<File>("file1.txt");
		ResourceManager::AcquireResource<File>("file2.jpg");
		ResourceManager::AcquireResource<Sound>("file3.lol");

	}catch(const char* s){
		L(s);
	}

	return 0;
}