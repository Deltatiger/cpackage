#ifndef _cfunctions
 	#define _cfunctions
 	float get_chars_num(char c);
	# define IS_CHAR(x) ( (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
	# define IS_NUM(x) ((x >= '0' && x <= '9'))
 	#include "cfunctions.c"
#endif