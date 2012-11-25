#ifndef _cfunctions
 	#define _cfunctions
 	unsigned long int hash(unsigned char *str);
 	void package_init(struct _initList *init);
 	void package_exit(struct _initList *init);
 	#include "cfunctions.c"
#endif