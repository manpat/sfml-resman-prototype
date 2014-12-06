#ifndef LUAPARSER_H
#define LUAPARSER_H

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <string>
#include <list>
#include <map>

using std::string;

class ResourceNode;

class LuaParser{
private:
	static lua_State* l;
	static void checkAndInit();

	public: static std::list<ResourceNode> parsePack(const string& path);
	private: static std::list<ResourceNode> leafPack(const ResourceNode& node);
};

struct ResourceNode{
	bool isResourcePack;
	string alias;
	string path;
	string type;
};

#endif