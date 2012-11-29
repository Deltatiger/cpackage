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
	cWindowDetails.hiddenWindow = mWindow;
	gtk_widget_hide(mWindow);
	gtk_search_page();
	cWindowDetails.activeWindow = mWindow;
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
static void new_item_entry(GtkWidget *widget, gpointer data)	{
	const gchar *iName, *iPrice, *iQty;
	struct _newItem_entryIds *entry = data;
	productList *list;
	int count;
	char tempFilename[9];
	char tempPId[11];
	iName = gtk_entry_get_text(GTK_ENTRY(entry->entry1));
	iPrice = gtk_entry_get_text(GTK_ENTRY(entry->entry2));
	iQty = gtk_entry_get_text(GTK_ENTRY(entry->entry3));
	if(strlen(iName) <= 4 || strlen(iPrice) < 1 || strlen(iQty) < 2)	{
		gtk_label_set_text(GTK_LABEL(entry->messageLabel), "Not Enough Details.");
		return;
	}
	list = malloc(gInit.fileItemCount[iName[0]-101]*sizeof(productList));
	//We first check if there is one with the same name already present in the DB
	sprintf(tempFilename, "%c_db.txt", tolower(iName[0]));
	search_db(list, &count, iName, tempFilename);
	if(count == 0)	{
		sprintf(tempPId, "%d%d", tolower(iName[0] + 4), gInit.lItemNumber++);
		strcpy(list[0].name, iName);
		strcpy(list[0].id, tempPId);
		list[0].qty = atoi(iQty);
		list[0].price = atof(iPrice);
		db_write(list, -1, tempFilename);
		free(list);
		gtk_label_set_text(GTK_LABEL(entry->messageLabel), "Item Added to the Database.");
	} else {
		gtk_label_set_text(GTK_LABEL(entry->messageLabel), "Item Already Exists.");
	}
	gtk_entry_set_text(GTK_ENTRY(entry->entry1), "");
	gtk_entry_set_text(GTK_ENTRY(entry->entry2), "");
	gtk_entry_set_text(GTK_ENTRY(entry->entry3), "");
 }

 /*
  * @page : search.c
  */
void add_to_list(GtkWidget *list, const gchar *str)	{
	GtkListStore *store;
	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, str, -1);
}

void remove_all(GtkWidget *list)	{
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW (list)));
  model = gtk_tree_view_get_model (GTK_TREE_VIEW (list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) 
      return;
  gtk_list_store_clear(store);
}

void search_item_check(GtkWidget *widget, gpointer data)	{
	static lCharCount = 0;
	const gchar *text;
	int flag = 0,i;
	struct _search_entryData * entry = data; 
	productList temp[100];
	char filename[9], ch;
	text = gtk_entry_get_text(GTK_ENTRY(entry->entry));
	for(i= 0; text[i] != '\0'; i++)	{
		if(i == 0)	{
			if(IS_CHAR(text[i]))	{
				flag = -1;
			} else if(IS_NUM(text[i]))	{
				flag = 1;
			}
		} else {
			if((IS_CHAR(text[i]) && flag != -1) || (IS_NUM(text[i]) && flag != 1))	{
				//This is an error as the charecter types dont match.
				remove_all(entry->list);
				gtk_label_set_text(GTK_LABEL(entry->label), "Error. Not a valid ID or Name.");
				return;
			}
		}
	}
	ch = tolower(text[0]);
	//Now since the data is clean. We check it using search_db
	if(gInit.fileItemCount[ch-97] == 0)	{
		remove_all(entry->list);
		gtk_label_set_text(GTK_LABEL(entry->label), "No items found with that name.");
		return;
	}
	sprintf(filename, "%c_db.txt", tolower(text[0]));
	search_db(temp, &flag, text, filename);
	if(flag > 0)	{
		remove_all(entry->list);
		for(i = 0 ; i < flag; i++)	{
			add_to_list(entry->list, temp[i].name);
		}
	} else {
		gtk_label_set_text(GTK_LABEL(entry->label), "No items found with that name.");
	}
}

void search_item_show(GtkWidget *selection, gpointer label)	{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;
	char *filename;
	char dTemp[150];
	int count;
	productList temp;
	value = (char *)malloc(150 * sizeof(char));
	filename = (char *)calloc(10 , sizeof(char));
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))	{
		gtk_tree_model_get(model, &iter, 0, &value, -1);
		sprintf(filename, "%c_db.txt", tolower(value[0]));
		search_db(&temp, NULL, value, filename);
		g_print("%s %s", temp.name, temp.id);
		strcpy(dTemp, "");
		sprintf(dTemp, "%s %s\n%s %s\n%s %d\n%s %.2f", "Item Name :", temp.name, "Item ID :", temp.id, "Stock Left :", temp.qty, "Price Per Unit :", temp.price);
		gtk_label_set_text(GTK_LABEL(label), dTemp);
	}
	free(value);
	free(filename);
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
	gtk_widget_show(mWindow);
}