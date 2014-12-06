#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "resourcemanager.h"
#include "baseresource.h"

#include "logger.h"

using namespace std;

class Texture : public BaseResource{
private:
	sf::Texture texture;

public:
	Texture() : BaseResource(){}

	void load() override {
		L("Texture::load ", filePath);
		texture.loadFromFile(filePath);
	}
	void unload() override {
		L("Texture::unload ", filePath);
	}

	sf::Texture& get(){
		return texture;
	}

	static string Type(){
		return "texture";
	}
};

void printAllResources(){
	L("\n---- Managed Resources ----");

	auto l = ResourceManager::listAll();
	for(auto r : l){
		L("\t[", r->getType(), "]\t", r->getAlias(), 
			"\t", r->isLoaded()?"loaded":"not loaded");
	}

	L("---- Managed Resources ----\n");
}

int main(){
	try{
		InitLogFile("log.txt");
		ResourceManager::setLoadCompleteCallback([](){
			L("Loading complete");
		});
		ResourceFactory::addType<Texture>();
		ResourceManager::loadPack("resourcepacks/testpack.lua", LoadMode::Block);

		sf::RenderWindow window(sf::VideoMode(800, 600), "Things");

		auto res = ResourceManager::get<Texture>("squiggle");
		auto res2 = ResourceManager::get<Texture>("star");
		sf::Sprite sprite, sprite2;
		sprite.setTexture(res->get());
		sprite2.setTexture(res2->get());
		sprite2.setPosition(sf::Vector2f(128.f, 128.f));

		while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			sf::Event event;
			while(window.pollEvent(event)){
				if(event.type == sf::Event::Closed){
					window.close();
				}
			}

			window.clear();
			window.draw(sprite);
			window.draw(sprite2);
			window.display();
		}

	}catch(const char* e){
		L(e);
	}

	ResourceManager::cleanupUnused();
	return 0;
}

// int main(){
// 	try{
// 		InitLogFile("log.txt");

// 		ResourceManager::setLoadCompleteCallback([](){
// 			L("==============================");
// 			L("====== Loading complete ======");
// 			L("==============================");
// 		});

// 		L("\n--- Adding Resource Types ---");

// 		// Create class generating stubs
// 		ResourceFactory::addType<File>();
// 		ResourceFactory::addType<Sound>();

// 		L("\n--- Acquiring Individual Resources ---");

// 		// These resources haven't been loaded yet so 
// 		//	AcquireResource queues loading.
// 		auto r = ResourceManager::acquire<File>("file1.txt", LoadMode::Queue);
// 		ResourceManager::load("file2.jpg", File::Type(), LoadMode::Block);
// 		auto s = ResourceManager::acquire<Sound>("file3.lol");
// 		L("s ref count ", s.getRefCount());

// 		L("\n--- Acquiring Resource Pack ---");

// 		ResourceManager::loadPack("testpack.lua", LoadMode::Queue);

// 		L("\n--- Beginning update loop ---");

// 		// Waits until everything is loaded
// 		while(ResourceManager::isLoading()){
// 			ResourceManager::update();
// 			L("\t[frame stuff]");
// 		}

// 		printAllResources();
// 		// ResourceManager::unload("file2.jpg");
// 		// printAllResources();
// 		// ResourceManager::cleanupUnused();
// 		// printAllResources();

// 		L("\n--- Acquiring Resources Again ---");

// 		// All resources will now be loaded
// 		ResourceManager::get<File>("file1.txt");
// 		ResourceManager::acquire<File>("file2.jpg");
// 		ResourceManager::acquire<Sound>("file3.lol");

// 		L("\n--- Cleanup ---");

// 		ResourceManager::cleanupUnused();

// 		L("--- End ---");

// 	}catch(const char* s){
// 		L(s);
// 	}

// 	return 0;
// }