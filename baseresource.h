#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H

#include <string>

using std::string;

class BaseResource {
protected:
	string alias;
	string type;
	string filePath;
	bool loaded;
	size_t refCount;
	// size_t RAMUsage;

public:
	BaseResource(const string& path);

	void loadBase();
	void unloadBase();

	virtual void load();
	virtual void unload();
	virtual void reload();
	// static getErrorResource;

	static string Type();

	string getAlias() const;
	string getType() const;
	string getPath() const;
	size_t getRefCount() const;
	bool isLoaded() const;
};

#endif