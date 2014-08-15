#include "arx_sysmgr.h"
#include "arx_system.h"
#include <cassert>
#include <stdexcept>

namespace arx{

int SysMgr::RegSystem( SystemFactory* f ){
	int ret = 1;
	RMap::iterator i = _rsys.find( f->name );
	if( i == _rsys.end()){
		_rsys.insert( RMap::value_type( f->name, f));
		ret = 0;
	}
	return ret;
}

System* SysMgr::ActivateSystem( const char* name ){
	assert(0);
	System* ret = 0;
	RMap::iterator i = _rsys.find( name );
	if( i != _rsys.end()){
		if( _sys.find( name ) != _sys.end()){
			ret = i->second->Create( 0, 0 );
			if( ret )
				_sys.insert( SMap::value_type( name, ret));
		}
	}
	return ret;
}

int SysMgr::DeactivateSystem( const char* name ){
	assert(0);
	int ret = 1;
	SMap::iterator i = _sys.find( name );
	if( i != _sys.end()){
		System* s = i->second;
		
	}
	return ret;
}

int SysMgr::AddSystem( System* sys ){
	return _sys.insert( SMap::value_type( sys->GetName(), sys)).second;
}

int SysMgr::RemoveSystem( const char* str ){
	SMap::iterator t = _sys.find( str );
	int ret = 1;
	if( t != _sys.end()){
		_sys.erase( t );
		ret = 1;
	}
	return ret;
}

System* SysMgr::FindSystem( const char* str ){
	System* ret = 0;
	if( str ){
		SMap::iterator t = _sys.find( str );
		if( t != _sys.end()){
			ret = t->second;
		}
	}
	return ret;
}

int SysMgr::SetUpdateable( System* sys, int mode, const char* sys2 ){
	int ret = 1;
	SVec::iterator i = _udt.end();
	for( SVec::iterator j = _udt.begin(); j != _udt.end(); ++j){
		if( *j == sys ) {
			i = j;
			break;
		}
	}
	if( i == _udt.end()){
		if( mode == 0 ){
			_udt.push_back( sys );
			ret = 0;
		} else if( mode == 1 ){
			_udt.insert( _udt.begin(), sys );
			ret = 0;
		} else if( sys2 ){
			System* s = this->FindSystem( sys2);
			if( s ){
				i = _udt.begin();
				while( i != _udt.end() && *i != s )
					++i;
				if( *i == s ){
					if( mode == 2 ){
						_udt.insert( i + 1, sys);
						ret = 0;
					} else if( mode == 3 ){
						_udt.insert( i, sys);
						ret = 0;
					}
				}
			}
		}
	}
	return ret;
}

int SysMgr::Update( long ms ){
	int ret = 0;
	for( SVec::iterator i = _udt.begin(); i != _udt.end(); ++i){
		(*i)->Update( ms );
	}
	return ret;
}

int SysMgr::RemoveUpdateable( System* sys ){
	int ret = 1;
	SVec::iterator i = _udt.begin();
	while( i != _udt.end() && *i != sys ) ++i;
	if( *i == sys ) { 
		_udt.erase( i );
		ret = 0;
	}
	return ret;
}
}
