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
void gtk_sub_window_quit(GtkWidget *window, gpointer data)	{
	//If data is not null then we have to disconnect the destroy signal handler from the mWindow first
	int *delId;
	if(data != NULL)	{
		delId = data;
		g_signal_handler_disconnect(mWindow, *delId);
	}
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
	//Callback from the below function 
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
	mod_entry(temp,oData->id, filename, 1);
	//Now that the entry is made we close the window and set the entry in search.c to none
	gtk_widget_destroy(oData->window);
	gtk_widget_show(mWindow);
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
	//This deletes the entry from the list
	GtkTreeIter iter;
	GtkTreeModel *model;
	struct _search_modRecData *oData = data;
	char temp[9], *value;
	gtk_tree_selection_get_selected(GTK_TREE_SELECTION(oData->selection), &model, &iter);
	gtk_tree_model_get(model, &iter, 0, &value, -1);
	strcpy(temp, "");
	sprintf(temp, "%c_db.txt", tolower(value[0]));
	remove_entry(value, temp);
	//Now that the delete is done we set the entry to nothing
	gtk_entry_set_text(GTK_ENTRY(oData->entry), "");
}

/*
 * @page : newbill.c
 */
void newbill_entry_changed(GtkWidget *widget, gpointer data)	{
	const gchar *text;
	int flag = 0,i;
	struct _newbill_select_data * eData = data; 
	productList temp[100];
	char filename[9], ch;
	text = gtk_entry_get_text(GTK_ENTRY(eData->nameEntry));
	if(strlen(text) < 1)	{
		remove_all(eData->sugList);
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
			if(temp[i].qty <= 0)	{
				continue;
			}
			add_to_list(eData->sugList, temp[i].name);
		}
	}
}

void newbill_entry_add(GtkTreeView *treeView, GtkTreePath *path, GtkTreeViewColumn *column ,gpointer data)	{
	//@desc : This is used to add an entry to the text box entry for easy use
	//This is executed on a double click on the selection of list1
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	char * value;
	struct _newbill_select_data * fData = data;
	//We first get the selection and extract the data
	selection = gtk_tree_view_get_selection(treeView);
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))	{
		gtk_tree_model_get(model, &iter, 0, &value, -1);
		gtk_entry_set_text(GTK_ENTRY(fData->nameEntry), value);
	}
}

void add_item_to_billList(GtkWidget *list, productList *product, int qty, int itemCount)	{
	//This adds the productList to the list
	GtkListStore *store;
	GtkTreeIter iter;
	char *str;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, itemCount+1, 1, product->id, 2 , product->name, 3 , qty, 4, qty*product->price,-1);
}

void newbill_add_item(GtkEntry *entry, gpointer data)	{
	//Now we have the product and the qty. We add the item to the billing list
	struct _newbill_select_data *oData = data;
	productList temp;
	char fileName[7];
	char pName[25];
	char buff[75];
	int count, i;
	int bItemCount = 0;
	float tCost = 0;
	strcpy(pName, gtk_entry_get_text(GTK_ENTRY(oData->nameEntry)));
	sprintf(fileName, "%c_db.txt", pName[0]);
	search_db(&temp, &count, (const char *)pName, (const char *)fileName);
	if(temp.name[0] == '\0' || temp.qty <= 0)	{
		return;
	}
	count = atoi(gtk_entry_get_text(GTK_ENTRY(oData->qtyEntry)));
	if(temp.qty < count)	{
		return;
	}
	temp.qty = count;
	add_item_to_billList(oData->billList, &temp, count, oData->productCount++);
	oData->bList[oData->productCount-1] = temp;
	for(i = 0; i < oData->productCount; i++)	{
		bItemCount += oData->bList[i].qty;
		tCost += oData->bList[i].qty * oData->bList[i].price;
	}
	sprintf(buff, "Total Items Count : %d\nTotal cost of Items : %.2f", bItemCount, tCost);
	gtk_label_set_text(GTK_LABEL(oData->label), buff);
	gtk_entry_set_text(GTK_ENTRY(oData->nameEntry), "");
	gtk_entry_set_text(GTK_ENTRY(oData->qtyEntry), "");
}

void newbill_done(GtkWidget *widget, gpointer data)	{
	//We show them the total amount and total no of items in a popup
	struct _newbill_select_data *oData = data;
	int i, iTemp;
	FILE *fp;
	char temp[15];
	productList pLTemp;
	//We check if there is file with the current bill number
	sprintf(temp, "db/bill/%d.dat", gInit.lBillNumber++);
	fp = fopen(temp, "r");
	if(fp != NULL)	{
		//WE just increement the bill number for now.
		gInit.lBillNumber++;
		sprintf(temp, "db/bill/%d.dat", gInit.lBillNumber++);
		fclose(fp);
		fp = fopen(temp, "w");
	} else {
		fclose(fp);
		fp = fopen(temp, "w");
	}
	fprintf(fp, "%d|%d\n", gInit.lBillNumber-1, oData->productCount);
	for(i = 0 ; i < oData->productCount; i++)	{
		//First we make the required changes in the db files.
		sprintf(temp, "%c_db.txt", tolower(oData->bList[i].name[0]));
		search_db(&pLTemp, &iTemp, oData->bList[i].name, temp);
		pLTemp.qty -= oData->bList[i].qty;
		//This is for adding a low stock warning
		if(pLTemp.qty <= QTY_LOW_WARN)	{
			g_print("\nAdding low stock warning...");
			add_low_stock_warning(pLTemp);
		}
		mod_entry(pLTemp, oData->bList[i].name, temp, 0);
		fprintf(fp, "#%s|%s|%d|%f#\n", oData->bList[i].id, oData->bList[i].name, oData->bList[i].qty, oData->bList[i].price);
	}
	fclose(fp);
	//Now we reset all the data 
	gtk_label_set_text(GTK_LABEL(oData->label), "");
	gtk_entry_set_text(GTK_ENTRY(oData->nameEntry), "");
	gtk_entry_set_text(GTK_ENTRY(oData->qtyEntry), "");
	remove_all(oData->billList);
}

void main_gtk_set_statistics(GtkWidget *list)	{
	//we update the staticstics window
	FILE *fp;
	int totalItem = 0, i;
	char totalCost[15];
	char temp[50];
	remove_all(list);
	for(i = 0; i < 26; i++)	{
		totalItem += gInit.fileItemCount[i];
	}
	sprintf(temp, "Last Bill Number : %d", gInit.lBillNumber);
	add_to_list(list, temp);
	sprintf(temp, "Total Items      : %d", totalItem);
	add_to_list(list, temp);
}

void main_gtk_set_lowstock(GtkWidget *list)	{
	//We update the low stock window
	FILE *fp;
	int count, i;
	char temp[25], filename[10];
	productList pTemp;
	remove_all(list);
	//We open the file and get the details and add it to the list
	fp = fopen("../db/lowstock.txt", "r");
	fscanf(fp, "$ %d $\n", &count);
	g_print("\n Count is : %d", count);
	if(count == 0)	{
		add_to_list(list, "Well Stocked Inventory");
	}
	for(i = 0; i < count; i++)	{
		fscanf(fp, "# %s #\n", temp);
		sprintf(filename, "%c%c%c", temp[0], temp[1], temp[2]);
		sprintf(filename, "%c_db.txt", atoi(filename)-4);
		search_db(&pTemp, NULL, temp, filename);
		if(pTemp.name[0] == '\0' )	{
			continue;
		}
		add_to_list(list, pTemp.name);
	}
	fclose(fp);
}