/* This is the main file that holds the only main method*/
#include <stdio.h>
#include "cdatatypes.h"
#include "db.h"

int main()	{
	struct productList t[20000];
	int count, i;
	get_from_db(t, &count, "b_db.txt");
	for(i = 10000; i < 20000; i++)	{
		printf("%s %s %d %f\n", t[i].id, t[i].name, t[i].qty, t[i].price );
	}
	return 0;
}