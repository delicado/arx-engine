#ifndef ARX_COMPONENT_H
#define ARX_COMPONENT_H

#include "arx_declares.h"
#include "arx_containers.h"

namespace arx {

class System;

class Component {
	typedef Vector< System*>  ContSys; 
	void **_dta;
	int _dsz;
	ContSys _sys;
public:
	Component();
	Component( void ** dta, int dsz );
	virtual ~Component();
	int AddSystem( System* sys );
	int RemoveSystem( System* sys );
	void* GetData( IDEntity id );
	void SetData( IDEntity id, void* data);
	int AddEntity( IDEntity id );
	int RemoveEntity( IDEntity id );
};

}

#endif