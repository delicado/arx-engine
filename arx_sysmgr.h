#ifndef ARX_SYSMGR_H
#define ARX_SYSMGR_H

#include "arx_containers.h"
#include "arx_cstring.h"

namespace arx {

class System;
class SystemFactory;

class SysMgr {
	typedef  Map< CString< char>, System*>	SMap;
	typedef  Map< CString< char>, SystemFactory*> RMap;
	typedef  Vector< System*> SVec;
	SMap   _sys;	//active systems
	SVec   _udt;	//updateable systems
	RMap   _rsys;   //system factory
public:
	int RegSystem( SystemFactory* f );
	System* ActivateSystem( const char* name );
	int DeactivateSystem( const char* name );
	int AddSystem( System* sys );
	int RemoveSystem( const char* str );
	System* FindSystem( const char* str );
	// 0 - insert last.
	// 1 - insert first.
	// 2 - insert after.
	// 3 - insert before.
	int SetUpdateable( System* sys, int mode = 0, const char* sys2 = 0 );
	int RemoveUpdateable( System* sys );
	int Update( long ms );
};
	
	
}


#endif