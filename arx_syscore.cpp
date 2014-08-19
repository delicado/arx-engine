#include "arx_syscore.h"
#include "arx_sysmgr.h"
#include "arx_system.h"
#include "arx_opscript.h"
#include <stdio.h>
#include <cassert>

namespace arx {

Arx* Arx::instance = 0;

int Arx::SLoadScriptOps( lua_State* s ){
/*
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
	*/
	printf( "native code!" );
	return 0;
}

int Arx::SUnloadScriptOps( lua_State* s ){
/*
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
*/
return 0;
}
 
Arx::Arx(){
	_smgr = 0;
	_lmgr = 0;
	instance = this;
}

int Arx::Initialize(){
	int ret = 0;
	_smgr = new SysMgr;
	_lmgr = new ScriptMgr( this );
	_lmgr->Initialize();
	_lmgr->AddScriptOp( SLoadScriptOps, "LoadOps");
	_lmgr->AddScriptOp( SUnloadScriptOps, "UnloadOps");
	return ret;
}

int Arx::Log( const char* str ){
	printf( "%s\n", str );
	return 0;
}

SysMgr* Arx::GetSysMgr() const {
	return _smgr;
}

ScriptMgr* Arx::GetScriptMgr() const {
	return _lmgr;
}

}
