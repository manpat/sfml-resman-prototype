#include "resourcebase.h"
#include "logger.h"

ResourceBase::ResourceBase(const string& _path)
	: path(_path), isLoaded(false){

}

void ResourceBase::LoadBase(){
	Load();

	isLoaded = true;
}
void ResourceBase::UnloadBase(){
	Unload();

	isLoaded = false;
}

void ResourceBase::Load(){
	L("Tried to load resource base");
}
void ResourceBase::Unload(){
	L("Tried to unload resource base");
}

string ResourceBase::Type(){
	return "generic";
}

string ResourceBase::GetType() const{
	return type;
}

string ResourceBase::GetPath() const{
	return path;
}
bool ResourceBase::IsLoaded() const{
	return isLoaded;
}
