
/*void get_entire_db1(struct *productLits[], int count)	{
	FILE *fp;
	char ch;
	int id[20000];
	char temp[15];
	char name[20000][20];
	int qty[20000];
	char price[20000][10];
	int i = 0, j = 0 ,k  = 0;
	fp = fopen("a_db.txt", "r");
	ch = getc(fp);
	while(ch != EOF)	{
		if(ch != '#')	{
			if(ch == '|')	{
				if( k == 0)	{
					temp[j] = '\0';
					id[i] = get_num(temp);
				} else if( k == 1)	{
					name[i][j] = '\0';
				} else	{
					temp[j] = '\0';
					qty[i] = get_num(temp);
				}
				j = 0;
				k++;
			} else {
				if (k == 0)	{
					//Store in id
					temp[j] = ch;
				} else if( k == 1)	{
					//store in name
					name[i][j] = ch;
				} else if(k == 2)	{
					//Store in qty
					temp[j] = ch;
				} else {
					//store in price
					price[i][j] = ch;
				}
				j++;
			}
		} else {
			price[i][j] = '\0';
			i++;
			k = 0;
			j = 0;
		}
		ch = getc(fp);
	}
	for(j = 0; j < i; j++)	{
		printf("%d %d\n", id[j], qty[j]);
	}
}*/

void get_entire_db(struct productList *t, int *count)	{
	FILE *fp;
	int i =0 , j = 0 ,k = 0;
	char temp[15], ch;
	void *ptr[4];
	fp = fopen("b_db.txt", "r");
	ch = getc(fp);	
	ptr[0] = &t[i].id[0];
	ptr[1] = &t[i].name[0];
	ptr[2] = &t[i].qty;
	ptr[3] = &t[i].price;
	while(ch != EOF)	{
		if(ch != '#')	{
			if(ch == '|')	{
				temp[k] = '\0';
				if(j == 0 || j == 1)	{
					strcpy((char *)ptr[j], temp);
				} else if(j == 2)	{
					*(int *)ptr[2] = get_i_num(temp); 
				} else {
					*(float *)ptr[3] = get_f_num(temp);
				}
				k = 0;
				j++;
			} else {
				if(ch == ' ' || ch == '\n')	{
					k--;
				} else {
					temp[k] = ch;
				}
				k++;
			}
		} else {
			temp[j] = '\0';
			i++;
			j = 0;
			k = 0;
		}
		ch = getc(fp);
	}
	*count = i;
}