#include "baseresource.h"
#include "logger.h"

BaseResource::BaseResource()
	: loaded(false){

}

void BaseResource::loadBase(){
	if(loaded) return;
	load();

	loaded = true;
}
void BaseResource::unloadBase(){
	if(!loaded) return;
	unload();

	loaded = false;
}
void BaseResource::reloadBase(){
	if(loaded){
		reload();
	}else{
		load();
	}

	loaded = true;
}

void BaseResource::load(){
	L("Tried to load resource base");
}
void BaseResource::unload(){
	L("Tried to unload resource base");
}
void BaseResource::reload(){
	L("Tried to reload resource base");
}

string BaseResource::Type(){
	return "generic";
}

string BaseResource::getAlias() const{
	return alias;
}
string BaseResource::getType() const{
	return type;
}
string BaseResource::getPath() const{
	return filePath;
}
bool BaseResource::isLoaded() const{
	return loaded;
}
