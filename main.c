/* This is the main file that holds the only main method*/
#include <stdio.h>
#include "cdatatypes.h"
#include "db.h"

int main()	{
	struct productList t[20000];
	int count, i;
	get_entire_db(t, &count);
	for(i = 0; i <= 10; i++)	{
		printf("%s %s %d %f\n", t[i].name, t[i].id, t[i].qty, t[i].price);
	}
	return 0;
}