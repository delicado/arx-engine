#ifndef ARX_OBJECT_H
#define ARX_OBJECT_H

#include "arx_config.h"
#include "arx_cstring.h"

namespace arx {
	
class Named {
	CString<ARX_CTYPE> _nm;
public:
	Named( const char* name );
	const char* GetName() const;
};

}
#endif