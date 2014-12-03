#include <iostream>
#include <vector>
#include "resourcemanager.h"
#include "baseresource.h"

#include "logger.h"

using namespace std;

class File : public BaseResource {
public:
	File(const string& path) 
		: BaseResource(path){

		type = Type();
	}

	void load() override {
		L("File::load ", filePath);
	}
	void unload() override {
		L("File::unload ", filePath);
	}

	static string Type(){
		return "file";
	}
};

class Sound : public BaseResource {
public:
	Sound(const string& p)
		: BaseResource(p){
		type = Type();
	}

	void load() override {
		L("Sound::load ", filePath);
	}
	void unload() override {
		L("Sound::unload ", filePath);
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
		ResourceFactory::addType<File>();
		ResourceFactory::addType<Sound>();

		L("\n--- Acquiring Resources ---");

		// These resources haven't been loaded yet so 
		//	AcquireResource queues loading.
		ResourceManager::acquire<File>("file1.txt");
		ResourceManager::load("file2.jpg", File::Type(), LoadMode::Block);
		auto s = ResourceManager::acquire<Sound>("file3.lol");

		L("\n--- Beginning update loop ---");

		// Waits until everything is loaded
		while(ResourceManager::isLoading())
		// while(!s->IsLoaded())
			ResourceManager::update();

		L("\n--- Acquiring Resources Again ---");

		// All resources will now be loaded
		ResourceManager::acquire<File>("file1.txt");
		ResourceManager::acquire<File>("file2.jpg");
		ResourceManager::acquire<Sound>("file3.lol");

	}catch(const char* s){
		L(s);
	}

	return 0;
}