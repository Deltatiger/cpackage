/* This is the main file that holds the only main method*/
#include <stdio.h>
#include "cdatatypes.h"
#include "db.h"

int main()	{
	struct productList t[20000];
	int count;
	get_entire_db(t, &count);
	return 0;
}