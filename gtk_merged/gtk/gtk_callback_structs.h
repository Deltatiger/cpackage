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
};

