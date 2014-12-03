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

public:
	static std::list<ResourceNode> parsePack(const string& path);
	static std::list<ResourceNode> parsePackSingleLevel(const string& path);
};

struct ResourceNode{
	bool isResourcePack;
	std::map<string, string> values;
};

#endif