#include "luaparser.h"
#include "logger.h"

#include <algorithm>
#include <vector>

lua_State* LuaParser::l = nullptr;

void LuaParser::checkAndInit(){
	if(!l){
		L("Initing lua");
		l = luaL_newstate();
		luaL_openlibs(l);
	}
}

static string lsat(lua_State* l, int i){
	int t = lua_type(l, i);
	switch(t) {
		case LUA_TSTRING:  /* strings */
		return string(lua_tostring(l, i));

		case LUA_TBOOLEAN:  /* booleans */
		return string(lua_toboolean(l, i) ? "true" : "false");

		case LUA_TNUMBER:  /* numbers */
		return std::to_string(lua_tonumber(l, i));

		default:  /* other values */
		return string(lua_typename(l, t));
	}
}

std::list<ResourceNode> LuaParser::parsePack(const string& path){
	checkAndInit();

	std::vector<string> packsLoaded = {path};
	std::list<ResourceNode> nodes = parsePackSingleLevel(path);

	bool done = false;

	while(!done){
		done = true;
		for(auto i = nodes.begin(); i != nodes.end(); i++){
			if(i->isResourcePack){
				L("Resource pack");

				if(std::find(packsLoaded.begin(), packsLoaded.end(), i->values["path"])
					!= packsLoaded.end()){
					L("\tCyclic dependency detected: ", i->values["path"]);
				}else{
					done = false;
					auto subnodes = parsePackSingleLevel(i->values["path"]);

					nodes.splice(nodes.end(), subnodes);
					packsLoaded.push_back(i->values["path"]);
				}

				i = nodes.erase(i);
			}
		}
	}

	return nodes;
}

std::list<ResourceNode> LuaParser::parsePackSingleLevel(const string& path){
	checkAndInit();

	L("Parsing file ", path);
	if(luaL_dofile(l, path.data()) != 0){
		L(lua_tostring(l, -1));
	}

	std::list<ResourceNode> nodes;

	// Resource pack table should be on stack

	lua_pushnil(l);
	while(lua_next(l, -2) != 0){
		lua_pushnil(l);

		ResourceNode n;
		n.isResourcePack = false;

		while(lua_next(l, -2) != 0){
			string key = lsat(l, -2);
			string value = lsat(l, -1);
			if(key == "type" && value == "resourcepack"){
				n.isResourcePack = true;
			}else{
				n.values[key] = value;
			}
			lua_pop(l, 1);
		}

		nodes.push_back(n);

		lua_pop(l, 1);
	}

	return nodes;
}