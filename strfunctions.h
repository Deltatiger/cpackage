/*
 * These are some required headers for the functions to work
 */
#ifndef _math
 #define _math
 #include <math.h>
#endif
#ifndef _string
 #define _string
 #include <string.h>
#endif


#ifndef _strfunctions
 	#define _strfunctions
 	int get_i_num(char *s);
 	float get_f_num(char *p);
 	#include "strfunctions.c"
#endif