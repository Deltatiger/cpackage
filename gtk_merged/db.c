void get_from_db(productList *t, int *count, const char *fileName)	{
	//Gets all the data from the file , puts them into the productLists array and sets count
	FILE *fp;
	int i =0 , j = 0 ,k = 0;
	char temp[50], ch;
	char filePath[12] = {"db/"};
	strcat(filePath, fileName);
	fp = fopen(filePath, "r");
	ch = getc(fp);	
	while(ch != EOF)	{
		if(ch != '#')	{
			if(ch == '|')	{
				temp[k] = '\0';
				if(j == 0)	{
					strcpy(&t[i].id[0], temp);
				} else if(j == 1)	{
					strcpy(&t[i].name[0], temp);
				}	else if(j == 2)	{
					t[i].qty = atoi(temp); 
				}
				k = 0;
				j++;
			} else {
				if(ch == '\n')	{
					k--;
				} else {
					temp[k] = ch;
				}
				k++;
			}
		} else {
			temp[k] = '\0';
			t[i].price= atof(temp);
			i++;
			j = 0;
			k = 0;
		}
		ch = getc(fp);
	}
	*count = i;
}

void db_write(productList *t, int count, const char *fileName)	{
	//This functions writes/rewirtes the structures to the datafile
	char temp[125];
	FILE *fp;
	int i = 0, j = 0;
	char filePath[12] = {"db/"};
	strcat(filePath, fileName);
	fp = fopen(filePath, (count == -1 ? "a" : "w"));
	if(count == -1)	{
		//Append data to the Filename file
		sprintf(temp, "%s|%s|%d|%f#\n", t->id, t->name, t->qty, t->price);
		while(temp[i] != '\0')	{
			fputc(temp[i++], fp);
		}
		fclose(fp);
	}else {
		//Deletes the file and rewrites the data
		while(i < count)	{
			if(t[i].id[0] != '\0')	{
				sprintf(temp, "%s|%s|%d|%f#\n", t[i].id, t[i].name, t[i].qty, t[i].price);
				j = 0;
			} else {
				i++;
				continue;
			}
			while(temp[j] != '\0')	{
				fputc(temp[j++], fp);
			}
			i++;
		}
	}
}

void remove_entry(const char *nameId, const char *fileName)	{
	//This removes the entry and then puts it back into the file.
	productList temp[1000];
	int count, i, type;
	get_from_db(temp, &count, fileName);
	type = IS_NUM(nameId[0]);
	for(i = 0; i < count; i++)	{
		if(type == 0)	{
			if(strcmp(temp[i].name, nameId) == 0)	{
				strcpy(temp[i].name, "");
				strcpy(temp[i].id, "");
				temp[i].qty = 0;
				temp[i].price = 0;
				break;
			}
		} else {
			if(strcmp(temp[i].id, nameId) == 0)	{
				strcpy(temp[i].name, "");
				strcpy(temp[i].id, "");
				temp[i].qty = 0;
				temp[i].price = 0;
				break;
			}
		}
	}
	db_write(temp, count, fileName);
}
void mod_entry(productList newDetails, const char *replaceNameId, const char *fileName)	{
	//Here the product name may have changed. So we open up the old one with the id or name and delete it. Then we write it anew where ever we need. But with the same id
	int count, i, type;
	char tFileName[11];
	//We delete the old one.
	strcpy(tFileName, "");
	g_print("%s", replaceNameId);
	if(IS_NUM(replaceNameId[0]))	{
		sprintf(tFileName, "%c%c%c", replaceNameId[0],replaceNameId[1],replaceNameId[2]);
		sprintf(tFileName, "%c_db.txt", atoi(tFileName)-4);
		remove_entry(replaceNameId, tFileName);
	} else {
		sprintf(tFileName, "%c_db.txt", replaceNameId[0]);
		remove_entry(replaceNameId, tFileName);
	}
	//Now that the old one is gone. We add a new one
	strcpy(newDetails.id, get_new_product_id(newDetails.name));
	db_write(&newDetails, -1, fileName);
}

void search_db(productList *listOfEntries, int * const count, const char *nameId, const char *fileName)	{
	productList temp[100];
	int tempCount = 0, i = 0, j = 0, type;
	//This is a precaution for when searching for a single exact value
	if(count != NULL)	{
		*count = 0;
	}
	get_from_db(temp, &tempCount, fileName);
	type = IS_NUM(nameId[0]);
	for(i = 0; i < tempCount; i++)	{
		if(type == 1)	{
			if(strstr(temp[i].id, nameId) != NULL)	{
				listOfEntries[j++] = temp[i];
			}
		} else {
			if(strstr(&temp[i].name[0], &nameId[0]) != NULL)	{
				listOfEntries[j++] = temp[i];
			}
		}
	}
	if(count != NULL)	{
		*count = j;
	}
	if(j == 0)	{
		listOfEntries = NULL;
	}
}

//This is a function to read the entrie file and return the string
char * read_entire_file(const char * fileName)	{
	FILE *fp;
	static char temp[100];
	int i = 0;
	char ch;
	fp = fopen(fileName, "r");
	//We return NULL if we cant open the damn file.
	if(fp == NULL)	{
		return NULL;
	}
	ch = getc(fp);
	while(ch != EOF)	{
		temp[i++] = ch;
		ch = getc(fp);
	}
	temp[i] = '\0';
	return temp;
}