#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H

#include <string>

using std::string;

class BaseResource {
protected:
	string alias;
	string type;
	string filePath;
	bool isLoaded;
	size_t refCount;
	// size_t RAMUsage;

public:
	BaseResource(const string& path);

	void LoadBase();
	void UnloadBase();

	virtual void load();
	virtual void unload();
	virtual void reload();
	// static getErrorResource;

	static string Type();

	string GetPath() const;
	string GetType() const;
	bool IsLoaded() const;
};

#endif