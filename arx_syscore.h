#ifndef ARX_SYSCORE_H 
#define ARX_SYSCORE_H

class lua_State;
typedef int (*lua_CFunction)(lua_State*);

namespace arx {

class SysMgr;

/*
  types: 
  0 - integer
  1 - float
  2 - char
  3 - string
*/
struct ScriptObjDesc {
	const char* name;
	int type;
	void* ptr;
	int size;
};

class Arx {
protected:
	void dls();
	static int SLoadScriptOps( lua_State* );
	static int SUnloadScriptOps( lua_State* );
	SysMgr*	_smgr;
public:
	Arx();
	static Arx* instance;
	lua_State*  ls;
	
	int Initialize();
	int RunScript( const char* filename );
	int Close();
	int Log( const char* str );
	int AddScriptOp( lua_CFunction f, const char* name );
	int RemScriptOp( const char* name );
	SysMgr* GetSysMgr();
};

}

#endif