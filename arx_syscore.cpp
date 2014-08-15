#include "arx_syscore.h"
#include "arx_sysmgr.h"
#include "arx_system.h"

#include <stdio.h>

extern "C" {
#include "./depends/lua-5.2.2/lua.h"
#include "./depends/lua-5.2.2/lauxlib.h"
#include "./depends/lua-5.2.2/lualib.h" 
}

#include <cassert>

namespace arx {

Arx* Arx::instance = 0;

int Arx::SLoadScriptOps( lua_State* s ){
	int ret = 1;
	const char* name = lua_tostring( instance->ls, -1);
	System* sys = Arx::instance->GetSysMgr()->FindSystem( name);
	if( sys ){
		if( sys->LoadScriptOps( instance ) ){
			ret = 0;
		}
	}
 	lua_pushinteger( instance->ls, ret );			 
	return 1;
}

int Arx::SUnloadScriptOps( lua_State* s ){
	int ret = 1;
	const char* name = lua_tostring( instance->ls, -1);
	if( name ){
		System* sys = Arx::instance->GetSysMgr()->FindSystem( name);
		if( sys ){
			if( sys->UnLoadScriptOps( instance ) ){
				ret = 0;
			}
		}
	}
	lua_pushinteger( instance->ls, ret ); 
	return 1; 
}
 
Arx::Arx(){
	ls = 0;
	_smgr = 0;
	instance = this;
}

void Arx::dls(){
	printf( "\nstack: %i\n", lua_gettop( ls ));
}

int Arx::AddScriptOp( lua_CFunction f, const char* name ){
    lua_getglobal( ls, "arx");
	lua_pushcfunction( ls, f );
	lua_setfield( ls, -2, name);
	lua_pop( ls, 1);
	return 0;
}

int Arx::RemScriptOp( const char* name ){
	lua_getglobal( ls, "arx");
	lua_pushnil( ls);
	lua_setfield( ls, -2, name);
	lua_pop( ls, 1);
	return 0;
}

int Arx::Initialize(){
	int ret = 0;
	_smgr = new SysMgr;
	ls = luaL_newstate();
	lua_newtable( ls);
	lua_setglobal( ls, "arx");
	this->AddScriptOp( SLoadScriptOps, "LoadOps");
	this->AddScriptOp( SUnloadScriptOps, "UnloadOps");
	return ret;
}

int Arx::RunScript( const char* filename ){
	int ret = 0;
	ret = luaL_loadfilex( ls, filename, 0 );
	if( ret == LUA_OK ){
			luaL_openlibs( ls);
			ret = lua_pcall( ls, 0, 0, 0 );
			if( ret != LUA_OK) this->Log( lua_tostring( ls, -1));
		} else this->Log( lua_tostring( ls, -1));
	return ret;
}

int Arx::Close(){
 	int ret = 0;
 	if( ls ){
 		lua_close( ls );
 		ls = 0;
 	}
	return ret; 	
}

int Arx::Log( const char* str ){
	printf( "%s\n", str );
	return 0;
}

SysMgr* Arx::GetSysMgr(){
	return _smgr;
}

}
