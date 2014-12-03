#include "baseresource.h"
#include "logger.h"

BaseResource::BaseResource(const string& _path)
	: path(_path), isLoaded(false){

}

void BaseResource::LoadBase(){
	Load();

	isLoaded = true;
}
void BaseResource::UnloadBase(){
	Unload();

	isLoaded = false;
}

void BaseResource::Load(){
	L("Tried to load resource base");
}
void BaseResource::Unload(){
	L("Tried to unload resource base");
}

string BaseResource::Type(){
	return "generic";
}

string BaseResource::GetType() const{
	return type;
}

string BaseResource::GetPath() const{
	return path;
}
bool BaseResource::IsLoaded() const{
	return isLoaded;
}
