#include "arx_component.h"
#include "arx_system.h"

namespace arx {

Component::Component(){
	_dta= 0;
	_dsz= 0;
}

Component::Component( void ** dta, int dsz ){
	_dta = dta;
	_dsz = dsz;
}

Component::~Component(){
	
}

int Component::AddSystem( System* sys ){
	int ret = 1;
	for( ContSys::iterator t = _sys.begin(); t!=_sys.end(); ++t ){
		if( *t == sys ){
			ret = 0;
			break;
		}
	}
	if( ret ){
		_sys.push_back( sys );
	}
	return 0;
}

int Component::RemoveSystem( System* sys ){
	return 0;
}

void* Component::GetData( IDEntity id ){
	return _dta[ reinterpret_cast<int>(id) ];
}

void Component::SetData( IDEntity id, void* data){
	 _dta[ reinterpret_cast<int>(id) ] = data; 
}

int Component::AddEntity( IDEntity id ){
	int ret = 1;
	if( _dta && _dta[ id] == 0 ){
		for( ContSys::iterator i = _sys.begin(); i != _sys.end(); ++i ){
			(*i)->AddEntity( this, id );
		}
		ret = 0;
	}
	return ret;
}

int Component::RemoveEntity( IDEntity id ){
	int ret = 1;
	if( _dta[ id] == 0 ){
		for( ContSys::reverse_iterator i = _sys.rbegin(); i != _sys.rend(); ++i ){
			(*i)->RemoveEntity( this, id );
		}
		ret = 0;
	}
	return ret; 
}

}
