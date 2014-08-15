#include "arx_system.h"

namespace arx {

System::System( const char* name, const char* const * deps){
	_name = name;
	_flags = 0;
	_deps = deps;
}

System::~System(){}

const char * System::GetName() const{
	return _name;
}

int System::Initialize(){ 
	return 0; 
}

int System::AddEntity( Component* c, IDEntity id ){
	return 0;
}

int System::RemoveEntity( Component* c, IDEntity id ){
	return 0;
}

int System::LoadScriptOps( Arx* obj ){
	return 0;
}

int System::UnLoadScriptOps( Arx* obj ){
	return 0;
}

int System::Update( long ms ){
	return 0;
}

int& System::Flag(){
	return _flags;
}

}
