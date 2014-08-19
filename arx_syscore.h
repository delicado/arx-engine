#ifndef ARX_SYSCORE_H 
#define ARX_SYSCORE_H
 
class lua_State;
typedef int (*lua_CFunction)(lua_State*);

namespace arx {

class SysMgr;
class ScriptMgr;

class Arx {
protected:
	static int SLoadScriptOps( lua_State* );
	static int SUnloadScriptOps( lua_State* );
	SysMgr*	_smgr;
	ScriptMgr* _lmgr;
public:
	Arx();
	static Arx* instance;
	
	int Initialize();
	int Log( const char* s );
	SysMgr* GetSysMgr() const;
	ScriptMgr* GetScriptMgr() const;
};

}

#endif