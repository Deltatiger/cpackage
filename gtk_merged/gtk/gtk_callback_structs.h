//The main struct used to store some details of the open and hidden windows ( 1 each)
typedef struct _window_details	{
	//The active window details
	GtkWidget *activeWindow;
	GtkWidget *hiddenWindow;
} WindowDetails;

//Login.c Structs
struct _login_myEntries	{
	GtkWidget *entryName, *entryPass;
	int exitCallId;
};

//main_gtk.c Structs
struct _mainGtk_labelData	{
	GtkWidget *entryMessage, *entryStatistics;
};

//newitem.c Structs
struct _newItem_entryIds	{
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *entry3;
	GtkWidget *messageLabel;
};

//search.c Structs
struct _search_entryData	{
	GtkWidget *entry;
	GtkWidget *label;
	GtkWidget *list;
	GtkWidget *modDataButton , *delDataButton;
};

struct _search_modRecData	{
	GtkWidget *entry;
	GtkWidget *label;
	GtkTreeSelection *selection;
	GtkWidget *modDataButton , *delDataButton;
};

struct _search_2_modData	{
	GtkWidget *window;
	GtkWidget *nameEntry;
	GtkWidget *qtyEntry;
	GtkWidget *priceEntry;
	char id[11];
};

//Newbill.c
struct _newbill_select_data	{
	GtkWidget *nameEntry;
	GtkWidget *qtyEntry;
	GtkWidget *billList;
	GtkWidget *sugList;
	GtkWidget *label;
	GtkTreeSelection *selection;
	productList bList[50];
	int productCount;
};

