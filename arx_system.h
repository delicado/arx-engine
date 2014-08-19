#ifndef ARX_SYSTEM_H
#define ARX_SYSTEM_H

#include "arx_declares.h"

namespace arx {

class Component;
class Arx;
class System;

struct ScriptObjDesc {
	const char* name;
	void* ptr;
	short type;
	short size;
	
	enum {
		INTEGER,
		FLOAT,
		CHAR,
		CARRAY
	};
};
 
class SystemFactory {
public:
	const char* name;
	const char* const * deps;
	virtual System* Create( const void* blob, int size ) = 0;
	virtual int Destroy( System* sys ) = 0;
};

class System {
	const char* _name;
	int _flags;
	const char* const * _deps;
public:
	enum {
		F_SCRIPTOPS = 1
	};
System( const char* name, const char* const * deps = 0 );
virtual ~System();
virtual int Initialize();
virtual int AddEntity( Component* c, IDEntity id );
virtual int RemoveEntity( Component* c, IDEntity id );
virtual int LoadScriptOps( Arx* obj );
virtual int UnLoadScriptOps( Arx* obj );
virtual int Update( long ms );
const char * GetName() const;
int& Flag();
};

}


#endif