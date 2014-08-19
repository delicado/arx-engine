//#include "arx_component.h"
//#include "arx_system.h" 
//#include "arx_cstring.h"
#include "arx_syscore.h"
#include "arx_containers.h"
#include "arx_opscript.h"
//#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <stdlib.h>
#include <stdexcept>
//#include <string>

int main(){
/*

const char* s1 = "waka";
const char* s2 = "sepe";
#define Q <
#define S 14
arx::CString<char> t( s1 ), u( s2 );
std::string v( s1 ), w( s2 );
//printf("%i\n", v Q w );
printf( "%i %i", t Q u, v Q w);
const char* ci[ 14 ] = {
	"rsdiis",
	"wrtat",
	"seerr",
	"sghks",
	"135d",
	"ddhjjj",
	"sshjjj",
	"**",
	"66vmkk",
	"vbjkjs",
	"ddfghjk",
	"ljgfs",
	"waka",
	"waka.mims"
};

for( int i = 0; i < S; i++ ){
	std::string a1( ci[i] );
	arx::CString<char> b1( ci[i] );
for( int j = 0; j < S; j++){
	std::string a2( ci[j]);
    arx::CString<char> b2( ci[j] );
    printf( "%s %s : %i %i\n", ci[i], ci[j], a1 Q a2, b1 Q b2); 
}
}*/
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
ao.GetScriptMgr()->RunScript( "system.lua" );
ao.GetScriptMgr()->test();
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
