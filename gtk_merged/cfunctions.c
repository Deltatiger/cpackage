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
	g_print("\nNew ID Requested : %s\n", id);
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

void add_low_stock_warning(productList data)	{
	//Now we check if it already exists in the lowstock file
	FILE *fp;
	char temp[15];
	char oData[30][15];
	int count, i, flag = 0, flagId = 0;
	fp = fopen("db/lowstock.txt", "a+");
	fscanf(fp, "%d$", &count);
	if(count > 0)	{
		for(i = 0; i < count; i++)	{
			fscanf(fp, "%s#", temp);
			if(strcmp(temp, data.id) == 0)	{
				flag = 1;
				flagId = i;
			}
			strcpy(oData[i], temp);
		}
	}
	if(flag == 0)	{
		fclose(fp);
		//New one detected
		fp = fopen("db/lowstock.txt", "w");
		fprintf(fp, "%d$\n", count+1);
		for(i = 0; i < count; i++)	{
			fprintf(fp, "%s#\n", oData[i]);
		}
		fprintf(fp, "#%s#\n", data.id);
	}
	fclose(fp);
}