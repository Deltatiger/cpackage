#define _cdatatypes

typedef struct _productList
{
	/* This data type hold all the details of a product and is used when displaying the inventory*/
	char name[50];
	char id[11];
	int qty;
	float price;
} productList;

typedef struct _sProduct
{
	/* This is used when getting from a db. This is a reference and hence does not contain a qty */
	char name[25];
	char id[11];
	float price;
} sProduct;

struct _initList	{
	//This contains all the details related to the core working of the package.
	int lBillNumber;
	int lItemNumber;
	short int fileItemCount[26]; //This holds the number of items in each file so it will be easy for general Use.
} gInit;