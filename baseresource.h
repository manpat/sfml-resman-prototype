#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H

#include <string>

using std::string;

class BaseResource {
	friend class ResourceManager;
	friend class ResourceFactory;
protected:
	string alias;
	string type;
	string filePath;
	bool loaded;
	// size_t RAMUsage;

public:
	BaseResource();

	void loadBase();
	void unloadBase();
	void reloadBase();

	virtual void load();
	virtual void unload();
	virtual void reload();
	// static getErrorResource;

	static string Type();

	string getAlias() const;
	string getType() const;
	string getPath() const;
	bool isLoaded() const;
};

#endif