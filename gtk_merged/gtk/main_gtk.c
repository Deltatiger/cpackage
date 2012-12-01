extern GtkWidget *mWindow;
extern WindowDetails cWindowDetails;

void main_gtk_list_init(GtkWidget *list, char *heading);

int gtk_main_page()	{
	GtkWidget *window;
	GtkWidget *hBox, *vBoxMain, *vBoxTemp;
	GtkWidget *button;
	GtkWidget *entry;
	GtkWidget *list;
	GtkWidget *scrollWindow;
	char *temp;
	struct _mainGtk_labelData EData;

	//We start with the main window
	mWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	cWindowDetails.activeWindow = mWindow;
	cWindowDetails.hiddenWindow = NULL;
	gtk_window_set_title(GTK_WINDOW(mWindow), "Main");
	gtk_window_set_position(GTK_WINDOW(mWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(mWindow), 600, 600);
	gtk_window_set_resizable(GTK_WINDOW(mWindow), FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(mWindow), 20);
	g_signal_connect(mWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//We Create the first vBox which stores the columns 
	vBoxMain = gtk_vbox_new(FALSE, 10);

	//Now a hBox to add the elements in a row (i.e) A big label which contains data and two buttons 
	hBox = gtk_hbox_new(FALSE, 10);
	scrollWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request(scrollWindow, 350, 225);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollWindow), GTK_SHADOW_ETCHED_IN);
	list = gtk_tree_view_new();
	EData.entryMessage = list;
	gtk_widget_set_size_request(list, 350, 200);
	main_gtk_list_init(list, "Low Stock Warnings.");
	main_gtk_set_lowstock(list);
	gtk_container_add(GTK_CONTAINER(scrollWindow), list);
	gtk_box_pack_start(GTK_BOX(hBox), scrollWindow, 0, 0, 0);
	//Now the buttons on the left
	vBoxTemp = gtk_vbox_new(TRUE, 10);
	//This is for the New Bill
	button = gtk_button_new_with_label("New Bill");
	gtk_widget_set_size_request(button, 150, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(new_bill), &EData);
	gtk_box_pack_start(GTK_BOX(vBoxTemp), button, 0, 0, 0);
	//This is for Show inv
	button = gtk_button_new_with_label("Show Inventory");
	gtk_widget_set_size_request(button, 150, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(show_inv), &EData);
	gtk_box_pack_start(GTK_BOX(vBoxTemp), button, 0, 0, 0);
	//Now we add the vBoxTemp into the hBox and in turn that to the hBox
	gtk_box_pack_start(GTK_BOX(hBox), vBoxTemp, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBoxMain), hBox, 0, 0, 0);
	//Now we get the next set of stuff. (i.e) a entry for stats and two buttons
	hBox = gtk_hbox_new(FALSE, 10);
	scrollWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request(scrollWindow, 350, 225);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollWindow), GTK_SHADOW_ETCHED_IN);
	list = gtk_tree_view_new();
	EData.entryStatistics = list;
	gtk_widget_set_size_request(list, 350, 200);
	main_gtk_list_init(list, "Statistics");
	main_gtk_set_statistics(list);
	gtk_container_add(GTK_CONTAINER(scrollWindow), list);
	gtk_box_pack_start(GTK_BOX(hBox), scrollWindow, 0, 0, 0);
	//Now the button for Check Item
	vBoxTemp = gtk_vbox_new(TRUE, 10);
	button = gtk_button_new_with_label("Check Inventory");
	gtk_widget_set_size_request(button, 150, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(check_inv), &EData);
	gtk_box_pack_start(GTK_BOX(vBoxTemp), button, 0 , 0 ,0);
	//Now a button for New item
	button =gtk_button_new_with_label("New Item");
	gtk_widget_set_size_request(button, 150, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(new_item), &EData);
	gtk_box_pack_start(GTK_BOX(vBoxTemp), button, 0 , 0 ,0);
	//Now we add the vBoxTemp to hBox and finally to vBoxMain
	gtk_box_pack_start(GTK_BOX(hBox), vBoxTemp, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBoxMain), hBox, 0, 0, 0);
	//Now for the last set of buttons namely Configuration and Exit
	hBox = gtk_hbox_new(TRUE, 10);
	button = gtk_button_new_with_label("Exit");
	gtk_widget_set_size_request(button, 200, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(gtk_package_exit), NULL);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBoxMain), hBox, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(mWindow), vBoxMain);
	gtk_widget_show_all(mWindow);
	return 0;
}

void main_gtk_list_init(GtkWidget *list, char *heading)	{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(heading, renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	store = gtk_list_store_new(1, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

	g_object_unref(store);
}