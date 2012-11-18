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
#ifndef _stdlib
 #define _stdlib
 #include <stdlib.h>
#endif

#ifndef _db
 	#define _db
 	void get_from_db(struct productList *t, int *count, char *fileName);
 	void db_write(struct productList *t, int *count, const char *fileName);
 	void remove_entry(const char *nameId, const char *fileName);
 	void mod_entry(struct productList newDetails, const char *replaceNameId, const char *fileName);
	#include "db.c"
#endif

