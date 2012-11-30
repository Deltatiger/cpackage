//This function is used to create a hash to store the value more securely
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *(str++))	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}

//This initializes the gInit structure which holds some important value
void package_init(struct _initList *init)	{
	FILE *fp;
	short int i = 0;
	fp = fopen("init.dat", "r");
	rewind(fp);
	fscanf(fp, "%d|%d|", &init->lBillNumber, &init->lItemNumber);
	for(i = 0; i < 26; i++)	{
		fscanf(fp, "%d|", &init->fileItemCount[i]);
	}
	fclose(fp);
}

//This functions rewrites data back into the init file
void package_exit(struct _initList *init)	{
	FILE *fp;
	short int i = 0;
	fp = fopen("init.dat", "w");
	fprintf(fp, "%d|%d|", init->lBillNumber, init->lItemNumber);
	for(i =0; i< 26; i++)	{
		fprintf(fp, "%d|", init->fileItemCount[i]);
	}
	fclose(fp);
}

char * get_new_product_id(char * const p)	{
	//This generates the 10 digit long code.
	static char id[11];
	int fIdPart = tolower(p[0]) + 4;
	strcpy(id, "");
	sprintf(id, "%d%d%d%d", fIdPart/100, (fIdPart%100)/10, fIdPart%10,gInit.lItemNumber++);
	return id;
}

char * strtolower(const char * p)	{
	int i = 0;
	char *t;
	t = (char *)p;
	while(*t != '\0')	{
		*t = tolower(*t);
		t++;
	}
	return t;
}