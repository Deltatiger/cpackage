extern GtkWidget *mWindow;

enum	{
	LIST_ITEM = 0,
	N_COLUMNS
};

static void search_init_list(GtkWidget *list);

int gtk_search_page()	{
	GtkWidget *label;
	GtkWidget *entry;
	GtkWidget *button;
	GtkWidget *align;
	GtkWidget *vBox, *hBox;
	GtkWidget *temp;
	GtkWidget *scrollWindow;
	GtkWidget *list;
	GtkTreeSelection *selection;
	static struct _search_entryData data;
	static struct _search_modRecData mRecData;
	static int delId;

	//We set up the main window
	mWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mWindow), "Search");
	gtk_window_set_default_size(GTK_WINDOW(mWindow), 400, 500);
	gtk_window_set_position(GTK_WINDOW(mWindow), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(mWindow), 10);
	delId = g_signal_connect(mWindow, "destroy", G_CALLBACK(gtk_sub_window_quit), NULL);

	//We now set up and use the alignment options
	vBox = gtk_vbox_new(FALSE, 10);
	temp = gtk_hbox_new(FALSE, 5);
	label = gtk_label_new("Entry Product Name / ID");
	gtk_widget_set_size_request(label, 150, 30);
	gtk_box_pack_start(GTK_BOX(temp), label, 0, 0 ,0);

	entry = gtk_entry_new();
	data.entry = entry;
	mRecData.entry = entry;
	gtk_widget_set_size_request(entry, 150, 30);
	gtk_box_pack_start(GTK_BOX(temp), entry, 0 , 0 , 0);
	gtk_box_pack_start(GTK_BOX(vBox), temp, 0, 0 ,0);

	//We set up the scrolled window to help make the lists window scrollable.
	scrollWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollWindow), GTK_SHADOW_ETCHED_IN);
	//Now we create the most important list
	list = gtk_tree_view_new();
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);
	gtk_container_add(GTK_CONTAINER(scrollWindow), list);
	gtk_box_pack_start(GTK_BOX(vBox), scrollWindow, 0, 0 , 0);

	search_init_list(list);
	gtk_widget_set_size_request(list, 100, 150);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
	mRecData.selection = selection;
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

	label = gtk_label_new("Message Box.");
	data.label = label;
	mRecData.label = label;
	gtk_widget_set_size_request(label, 200, 250);
	gtk_box_pack_start(GTK_BOX(vBox), label, 0, 0, 0);

	//Now we add the delete and mod item buttons
	hBox = gtk_hbox_new(TRUE, 10);
	button = gtk_button_new_with_label("Mod Item Details");
	mRecData.modDataButton = button;
	data.modDataButton = button;
	gtk_widget_set_size_request(button, 150, 30);
	gtk_widget_set_sensitive(button, FALSE);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	g_signal_connect(button, "clicked", G_CALLBACK(search_item_mod), &mRecData);

	button = gtk_button_new_with_label("Delete Item");
	mRecData.delDataButton = button;
	data.delDataButton = button;
	gtk_widget_set_size_request(button, 150, 30);
	gtk_widget_set_sensitive(button, FALSE);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	g_signal_connect(button, "clicked", G_CALLBACK(search_item_del), &mRecData);
	g_signal_connect(G_OBJECT(selection), "changed", G_CALLBACK(search_item_show), &mRecData);

	//we add the hBox to the vBox and then to the mWindow
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 0);
	//We add the Return to Main button to the bottom
	button = gtk_button_new_with_label("Return to Main");
	gtk_widget_set_size_request(button, 200, 40);
	g_signal_connect(button, "clicked", G_CALLBACK(gtk_sub_window_quit), &delId);
	gtk_box_pack_start(GTK_BOX(vBox), button, 0, 0, 0);
	align = gtk_alignment_new(0.50, 0.50, 0, 0);
	gtk_container_add(GTK_CONTAINER(align), vBox);
	gtk_container_add(GTK_CONTAINER(mWindow), align);

	data.list = list;
	g_signal_connect(entry, "changed", G_CALLBACK(search_item_check), &data);

	gtk_widget_show_all(mWindow);

	return 0;
}

static void search_init_list(GtkWidget *list)	{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("List Items", renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

	g_object_unref(store);
}
