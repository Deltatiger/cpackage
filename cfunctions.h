#ifndef _cfunctions
 	#define _cfunctions
	# define IS_CHAR(x) ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
	# define IS_NUM(x) ((x >= '0' && x <= '9'))
 	unsigned long int hash(unsigned char *str);
 	#include "cfunctions.c"
#endif