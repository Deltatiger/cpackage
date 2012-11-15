double get_f_num(char *p)	{
	char *bDecimal = NULL, temp[15];
	int num, i;
	double decNum = 0;
	strcpy(temp, p);
	num = strlen(temp);
	for(i = 0; i < num; i++)	{
		if(temp[i] == '.')	{
			temp[i] = '\0';
			bDecimal = &temp[i+1];
		}
	}
	num = atoi(temp);
	if(bDecimal != NULL)	{
		for(i = 0; bDecimal[i] != '\0'; i++)	{
			if(bDecimal[i] == ' ' || bDecimal[i] == '\n')	{
				continue;
			}
			decNum += (get_chars_num(bDecimal[i]))/pow(10, i+1);
		}
	}
	decNum += num;
	return decNum;
}

int get_i_num(char *s)	{
		int num = 0;
		short int i;
		for(i = 0 ; s[i] != '\0'; i++)	{
			//TODO remove this
			if(s[i] == ' ' || s[i] == '\n')	{
				continue;
			}
			num = num * 10 + (s[i] - 48);
		}
		return num;
}
