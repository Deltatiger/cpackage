extern struct _initList gInit;
extern GtkWidget *mWindow;
extern WindowDetails cWindowDetails;

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

void quit_sub_window(GtkWidget *window, gpointer data)	{
	//This is used to close a pop-up window like feature
	gtk_widget_destroy(window);
	gtk_widget_show(mWindow);
}
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
	cWindowDetails.hiddenWindow = mWindow;
	gtk_widget_hide(mWindow);
	gtk_newbill_page();
	cWindowDetails.activeWindow = mWindow;
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
	productList list[100];
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
	//We first check if there is one with the same name already present in the DB
	sprintf(tempFilename, "%c_db.txt", tolower(iName[0]));
	search_db(list, &count, iName, tempFilename);
	if(count == 0)	{
		strcpy(tempPId,get_new_product_id((char *const)iName));
		strcpy(list[0].name, iName);
		strcpy(list[0].id, tempPId);
		list[0].qty = atoi(iQty);
		list[0].price = atof(iPrice);
		gInit.fileItemCount[tolower(iName[0])-97]++;
		db_write(list, -1, tempFilename);
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
	struct _search_entryData *entry = data; 
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
				gtk_widget_set_sensitive(entry->modDataButton, FALSE);
				gtk_widget_set_sensitive(entry->delDataButton, FALSE);
				gtk_label_set_text(GTK_LABEL(entry->label), "Error. Not a valid ID or Name.");
				return;
			}
		}
	}
	ch = tolower(text[0]);
	//Now since the data is clean. We check it using search_db
	if(gInit.fileItemCount[ch-97] == 0)	{
		remove_all(entry->list);
		gtk_widget_set_sensitive(entry->modDataButton, FALSE);
		gtk_widget_set_sensitive(entry->delDataButton, FALSE);
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
	//Function is used to get the data from the tree view and display the entire record onto the label area
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;
	char *filename;
	char dTemp[150];
	int count;
	productList temp;
	struct _search_modRecData * mData = label;
	value = (char *)malloc(30 * sizeof(char));
	filename = (char *)calloc(10 , sizeof(char));
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))	{
		gtk_tree_model_get(model, &iter, 0, &value, -1);
		sprintf(filename, "%c_db.txt", tolower(value[0]));
		search_db(&temp, NULL, value, filename);
		strcpy(dTemp, "");
		sprintf(dTemp, "%s %s\n%s %s\n%s %d\n%s %.2f", "Item Name :", temp.name, "Item ID :", temp.id, "Stock Left :", temp.qty, "Price Per Unit :", temp.price);
		gtk_label_set_text(GTK_LABEL(mData->label), dTemp);
		gtk_widget_set_sensitive(mData->modDataButton, TRUE);
		gtk_widget_set_sensitive(mData->delDataButton, TRUE);
	}
	free(value);
	free(filename);
}

void search_mod_entry(GtkWidget *widget, gpointer data)	{
	struct _search_2_modData *oData = data;
	productList temp;
	char filename[11];
	//We copy the details into the temp to use later
	strcpy(temp.name, gtk_entry_get_text(GTK_ENTRY(oData->nameEntry)));
	strcpy(temp.id, oData->id);
	temp.qty = atoi(gtk_entry_get_text(GTK_ENTRY(oData->qtyEntry)));
	temp.price = atof(gtk_entry_get_text(GTK_ENTRY(oData->priceEntry)));
	sprintf(filename, "%c_db.txt", temp.name[0]);
	//We send the file name of the old data
	mod_entry(temp,oData->id, filename);
}

void search_item_mod(GtkWidget *widget, gpointer data)	{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *entry;
	GtkWidget *vBox, *hBox;
	GtkWidget *alignment;
	GtkWidget *label;
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;
	char *filename;
	char tempCStr[15];
	static productList temp;
	struct _search_modRecData *mData = data;
	static struct _search_2_modData modData;
	//Some dyanamic memory
	value = (char *)malloc(20 * sizeof(char));
	filename = (char *)calloc(10 , sizeof(char));
	//We Hide the main window for now.
	gtk_widget_hide(mWindow);
	//Now some pre - requisites like the struct with the original data
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(mData->selection), &model, &iter))	{
		gtk_tree_model_get(model, &iter, 0, &value, -1);
		strcpy(filename, "");
		sprintf(filename, "%c_db.txt", tolower(value[0]));
		search_db(&temp, NULL, value, filename);
	}
	//Now we create a new window above this. Then in a callback we reactivate
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	modData.window = window;
	gtk_window_set_default_size(GTK_WINDOW(window), 450, 500);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "Modify Entry");
	g_signal_connect(window, "destroy", G_CALLBACK(quit_sub_window), NULL);

	//A new vBox for alignment purposes
	vBox = gtk_vbox_new(TRUE, 10);

	//Now the three Entries and their labels in a hBox
	hBox = gtk_hbox_new(FALSE, 10);
	label = gtk_label_new("Product Name ");
	gtk_widget_set_size_request(label, 125, 50);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry = gtk_entry_new();
	modData.nameEntry = entry;
	gtk_widget_set_size_request(entry, 150, 50);
	gtk_entry_set_text(GTK_ENTRY(entry),temp.name);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 0);

	//Now for the Quantity
	hBox = gtk_hbox_new(FALSE, 10);
	label = gtk_label_new("Product Stock Left ");
	gtk_widget_set_size_request(label, 125, 50);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry = gtk_entry_new();
	modData.qtyEntry = entry;
	gtk_widget_set_size_request(entry, 150, 50);
	sprintf(tempCStr, "%d",temp.qty);
	gtk_entry_set_text(GTK_ENTRY(entry),tempCStr);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 0);

	//Now for the Price
	hBox = gtk_hbox_new(FALSE, 10);
	label = gtk_label_new("Product Price ");
	gtk_widget_set_size_request(label, 125, 50);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry = gtk_entry_new();
	modData.priceEntry = entry;
	gtk_widget_set_size_request(entry, 150, 50);
	sprintf(tempCStr, "%.3f", temp.price);
	gtk_entry_set_text(GTK_ENTRY(entry),tempCStr);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 0);

	//We set the id in the same struct used for the callback function
	strcpy(modData.id, temp.id);
	//Now for the submit button
	button = gtk_button_new_with_label("Submit");
	gtk_widget_set_size_request(button, 200, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(search_mod_entry), &modData);
	gtk_box_pack_start(GTK_BOX(vBox), button, 0, 0, 0);
	//Now for an alignment widget to put everything correctly.
	alignment = gtk_alignment_new(0.50, 0.50, 0, 0);
	gtk_container_add(GTK_CONTAINER(alignment), vBox);
	gtk_container_add(GTK_CONTAINER(window), alignment);
	gtk_widget_show_all(window);
}

void search_item_del(GtkWidget *button, gpointer data)	{

}

/*
 * @page : newbill.c
 */

void newbill_entry_changed(GtkWidget *widget, gpointer data)	{
	static lCharCount = 0;
	const gchar *text;
	int flag = 0,i;
	struct _newbill_select_data * eData = data; 
	productList temp[100];
	char filename[9], ch;
	text = gtk_entry_get_text(GTK_ENTRY(eData->nameEntry));
	if(strlen(text) < 1)	{
		return;
	}
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
				remove_all(eData->sugList);
				return;
			}
		}
	}
	ch = tolower(text[0]);
	//Now since the data is clean. We check it using search_db
	if(gInit.fileItemCount[ch-97] == 0)	{
		remove_all(eData->sugList);
		return;
	}
	sprintf(filename, "%c_db.txt", tolower(text[0]));
	search_db(temp, &flag, text, filename);
	if(flag > 0)	{
		remove_all(eData->sugList);
		for(i = 0 ; i < flag; i++)	{
			add_to_list(eData->sugList, temp[i].name);
		}
	}
}

void newbill_entry_add(GtkWidget *widget, gpointer data)	{

}

void newbill_done(GtkWidget *widget, gpointer data)	{

}