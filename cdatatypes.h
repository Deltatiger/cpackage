struct productList
{
	/* This data type hold all the details of a product and is used when displaying the inventory*/
	char name[25];
	char id[11];
	int qty;
	float price;
};

struct sProduct
{
	/* This is used when getting from a db. This is a reference and hence does not contain a qty */
	char name[25];
	char id[11];
	float price;
};