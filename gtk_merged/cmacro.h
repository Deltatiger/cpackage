#ifndef _cmacro
	#define _cmacro
	# define IS_CHAR(x) ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
	# define IS_NUM(x) ((x >= '0' && x <= '9'))
	# define QTY_LOW_WARN 5
#endif