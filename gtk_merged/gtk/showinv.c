extern GtkWidget *mWindow;
extern struct _initList gInit;

void add_item_showInv_list( productList item, GtkWidget *list);

int gtk_showinv_page()	{
	GtkWidget *alignment;
	GtkWidget *vBox;
	GtkWidget *list;
	GtkWidget *scrollWindow;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;
	static int delId;
	int i, count, j;
	char temp[10], temp2[11];
	productList pList[100];

	//we make the new main window
	mWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mWindow), "Complete Inventory");
	gtk_window_set_default_size(GTK_WINDOW(mWindow), 700, 600);
	gtk_window_set_position(GTK_WINDOW(mWindow), GTK_WIN_POS_CENTER);
	g_signal_connect(mWindow, "destroy", G_CALLBACK(gtk_sub_window_quit), NULL);

	//We add a scroll window
	scrollWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollWindow), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(scrollWindow, 650, 550);

	//We make a list view to fit everything
	list = gtk_tree_view_new();
	//We init the list here
	renderer = gtk_cell_renderer_text_new();
	//Column one
	column = gtk_tree_view_column_new_with_attributes("Product Id", renderer, "text", 0, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 100);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	//column two
	column = gtk_tree_view_column_new_with_attributes("Product Name", renderer, "text", 1, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 200);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	//column three
	column = gtk_tree_view_column_new_with_attributes("Product Stock", renderer, "text", 2, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 125);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	//cou=lumn four
	column = gtk_tree_view_column_new_with_attributes("Product Price", renderer, "text", 3, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 125);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	//Finalize the data
	store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT);
	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	g_object_unref(store);

	//Now that it is done we populate the list with all the data
	for(i = 0; i < 26; i++)	{
		if(gInit.fileItemCount[i] >= 0)	{
			sprintf(temp, "%c_db.txt", i+97);
			sprintf(temp2, "%c", i + 97);
			search_db(pList, &count, temp2, temp);
			for(j = 0; j < count; j++)	{
				add_item_showInv_list(pList[j], list);
			}
		}
	}
	gtk_container_add(GTK_CONTAINER(scrollWindow), list);
	alignment = gtk_alignment_new(0.50, 0.50, 0, 0);
	gtk_container_add(GTK_CONTAINER(alignment), scrollWindow);
	gtk_container_add(GTK_CONTAINER(mWindow), alignment);

	gtk_widget_show_all(mWindow);

	return 0;
}

void add_item_showInv_list( productList product, GtkWidget *list)	{
	//This adds the productList to the list
	GtkListStore *store;
	GtkTreeIter iter;
	char *str;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, 0, product.id, 1, product.name, 2 , product.qty, 3 , product.price,-1);
}