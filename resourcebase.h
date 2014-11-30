#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H

#include <string>

using std::string;

class ResourceBase {
protected:
	string path;
	string type;
	bool isLoaded;

public:
	ResourceBase(const string& path);

	void LoadBase();
	void UnloadBase();

	virtual void Load();
	virtual void Unload();

	static string Type();

	string GetPath() const;
	string GetType() const;
	bool IsLoaded() const;
};

#endif