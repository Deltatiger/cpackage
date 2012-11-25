extern struct _initList gInit;
extern GtkWidget *mWindow;
extern WindowDetails cWindowDetails;
/*
 * @page : Login.c
 */
//Used for logging the user in.
static void login_user(GtkWidget *widget,struct _login_myEntries *entry)	{
	const gchar *username, *password;
	gchar dbPass[25];
	GtkWidget *test;
	strcpy(dbPass, read_entire_file("initP.dat"));
	username = gtk_entry_get_text(GTK_ENTRY(entry->entryName));
	password = gtk_entry_get_text(GTK_ENTRY(entry->entryPass));
	//Now we check the data from the file.
	if(strcmp(password, dbPass) == 0)	{
		g_signal_handler_disconnect(mWindow, entry->exitCallId);
		gtk_widget_destroy(mWindow);
		//Now that the old widget is gone. Lets call the main_gtk
		gtk_main_page();
	}
}
/*
 * @page : main_gtk.c
 * @desc : Every function here just hides the mWindow and creates a new window
 */
static void new_bill(GtkWidget *widget, struct _mainGtk_labelData *data)	{
	g_print("New Bill Is Called.\n");
}
static void show_inv(GtkWidget *widget, struct _mainGtk_labelData *data)	{
	g_print("Show Inventory is Called.\n");
}
static void check_inv(GtkWidget *widget, struct _mainGtk_labelData *data)	{
	g_print("Check Inventory is Called.\n");
}
static void new_item(GtkWidget *widget, struct _mainGtk_labelData *data)	{
	cWindowDetails.hiddenWindow = mWindow;
	gtk_widget_hide(mWindow);
	gtk_newitem_page();
	cWindowDetails.activeWindow = mWindow;
}
static void config(GtkWidget *widget, struct _mainGtk_labelData *data)	{
	g_print("Config is Called.\n");
}
/*
 * @page : newitem.c
 */
static void new_item_entry(GtkWidget *widget, struct _newItem_entryIds *ent)	{
	const gchar *iName, *iPrice, *iQty;
	g_print("\n%p", ent->entry1);
	iName = gtk_entry_get_text(GTK_ENTRY(ent->entry1));
	iPrice = gtk_entry_get_text(GTK_ENTRY(ent->entry2));
	iQty = gtk_entry_get_text(GTK_ENTRY(ent->entry3));
	g_print("%s %s %s", iName, iPrice, iQty);
}

/*
 *@page : Globally Used Callbacks
 */

//Global exit function
void gtk_package_exit(GtkWidget *widget, gpointer data)	{
	package_exit(&gInit);
	gtk_main_quit();
}

//Used to close the active window and reload the hidden Window
void gtk_sub_window_quit()	{
	//This activates the hidden window and closes the active One.
	gtk_widget_destroy(mWindow);
	mWindow = cWindowDetails.activeWindow = cWindowDetails.hiddenWindow;
	cWindowDetails.hiddenWindow = NULL;
	gtk_widget_show_all(mWindow);
}