float get_f_num(char *p)	{
	char *temp1, *temp2;
	int num, i;
	float decNum = 0;
	temp1 = strtok(p, ".");
	temp2 = strtok(NULL, ".");
	num = get_i_num(temp1);
	for(i = 0; temp2[i] != '\0'; i++)	{
		if(temp2[i] == ' ' || temp2[i] == '\n')	{
			continue;
		}
		decNum += (temp2[i] - 48)/pow(10, i+1);
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
