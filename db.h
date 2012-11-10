/*
 * Some required libraries to make stuff work
 */
#ifndef _cdatatypes
 #include "cdatatypes.h"
#endif
#ifndef _strfunctions
 #include "strfunctions.h"
#endif
#ifndef _string
 #define _string
 #include <string.h>
#endif

#ifndef _db
 	#define _db
 	void get_entire_db(struct productList *, int *count);
	#include "db.c"
#endif

