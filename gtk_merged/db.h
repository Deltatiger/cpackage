/*
 * Some required libraries to make stuff work
 */
#ifndef _cdatatypes
 #include "cdatatypes.h"
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
 	void get_from_db(productList *t, int *count, const char *fileName);
 	void db_write(productList *t, int count, const char *fileName);
 	void remove_entry(const char *nameId, const char *fileName);
 	void mod_entry(productList newDetails, const char *replaceNameId, const char *fileName);
 	void search_db(productList *listOfEntries, int *const count, const char *nameId,const char *fileName);
 	char * read_entire_file(const char * fileName);
	#include "db.c"
#endif

