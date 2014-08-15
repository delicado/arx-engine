//#include "arx_component.h"
//#include "arx_system.h" 
//#include "arx_cstring.h"
#include "arx_syscore.h"
#include "arx_containers.h"
//#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <stdlib.h>
#include <stdexcept>
//#include <string>

int main(){

/*
const char* s1 = "acbyzzz";
const char* s2 = "acbyzzz";
#define Q <=
arx::CString<char> t( s1 ), u( s2 );
std::string v( s1 ), w( s2 );
//printf("%i\n", v Q w );
printf( "%i %i", t Q u, v Q w);*/
/*
typedef Map< arx::CString< char>, int > MP;

MP mp;
mp.insert( MP::value_type( "a", 100));
mp.insert( MP::value_type( "e", 100));
mp.insert( MP::value_type( "dee", 100));
mp.insert( MP::value_type( "c", 100));
mp.insert( MP::value_type( "b", 100));

for( MP::iterator i = mp.begin(); i != mp.end(); ++i ){
	printf( "%s\n", i->first.Data());
}
*/
arx::Arx ao;
ao.Initialize();
ao.RunScript( "system.lua" );

Vector< int> v;

for( int i = 0; i < 11; i++){
	v.push_back( i);
}

v.insert( v.end(), 99);
for( int i = 0; i < v.size(); i++){
	printf( "%i ", v[i]);
}

printf( "\nfinish\n");
return 0;
}
