extern GtkWidget *mWindow;
void newbill_init_list1(GtkWidget *list);
void newbill_init_list2(GtkWidget *list);
extern struct _initList gInit;

int gtk_newbill_page()	{
	GtkWidget *hBox;
	GtkWidget *vBox;
	GtkWidget *list1, *list2;
	GtkWidget *entry1, *entry;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *scrollWindow;
	GtkWidget *alignment;
	GtkTreeSelection *selection;
	char temp[50];
	static int delId;
	//Some static callback structs
	static struct _newbill_select_data	eData;
	eData.productCount = 0;
	//Now we create the required window
	mWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mWindow), "New Bill");
	gtk_window_set_default_size(GTK_WINDOW(mWindow), 700, 600);
	gtk_window_set_position(GTK_WINDOW(mWindow), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(mWindow), 10);
	delId = g_signal_connect(mWindow, "destroy", G_CALLBACK(gtk_sub_window_quit), NULL);

	//We create the vBox for alignment purposes
	vBox = gtk_vbox_new(FALSE, 20);
	//Now we set up a temprary hBox for alignment of stuff
	hBox = gtk_hbox_new(FALSE, 10);
	label = gtk_label_new("Enter Product Name :");
	gtk_widget_set_size_request(label, 125, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry1 = gtk_entry_new();
	eData.nameEntry = entry1;
	gtk_widget_set_size_request(entry1, 150, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry1, 0, 0, 0);
	label= gtk_label_new("Qty");
	gtk_widget_set_size_request(label, 100, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry = gtk_entry_new();
	eData.qtyEntry = entry;
	gtk_widget_set_size_request(entry, 150, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	//We add the hBox to the vBox;
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 0);
	//We add the text area to show the suggestions. This is also inside a scrollWindow
	scrollWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollWindow), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(scrollWindow, 300, 100);
	//Now we add the select window.
	list1 = gtk_tree_view_new();
	eData.sugList = list1;
	newbill_init_list2(list1);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list1), FALSE);
	gtk_container_add(GTK_CONTAINER(scrollWindow), list1);
	gtk_widget_set_size_request(list1, 250, 125);
	gtk_box_pack_start(GTK_BOX(vBox), scrollWindow, 0, 0, 0);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list1));
	eData.selection = selection;
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
	//We show the bill number
	sprintf(temp, "Bill No. : %d", gInit.lBillNumber);
	label = gtk_label_new(temp);
	gtk_widget_set_size_request(label, 150, 40);
	hBox = gtk_hbox_new(FALSE, 5);
	gtk_box_pack_end(GTK_BOX(hBox), label, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 0);
	//We now create the list inside of a scroll window
	scrollWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollWindow), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(scrollWindow, 300, 200);
	list2 = gtk_tree_view_new();
	eData.billList = list2;
	newbill_init_list1(list2);
	gtk_container_add(GTK_CONTAINER(scrollWindow), list2);
	gtk_box_pack_start(GTK_BOX(vBox), scrollWindow, 0, 0, 0);
	//We add the label that displays the total cost and item count
	label = gtk_label_new(NULL);
	eData.label = label;
	gtk_widget_set_size_request(label, 400, 50);
	gtk_box_pack_start(GTK_BOX(vBox), label, 0, 0, 0);
	//WE add the Done button at the last
	hBox = gtk_hbox_new(TRUE, 50);
	button = gtk_button_new_with_label("Done");
	gtk_widget_set_size_request(button, 150, 50);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	g_signal_connect(button, "clicked", G_CALLBACK(newbill_done), &eData);
	//We also add the cancel button at near the done button
	button = gtk_button_new_with_label("Cancel");
	gtk_widget_set_size_request(button, 150, 50);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	g_signal_connect(button,"clicked", G_CALLBACK(gtk_sub_window_quit), &delId);
	//We add the vBox to the container
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0 ,0);
	alignment = gtk_alignment_new(0.50, 0.50, 0, 0);
	gtk_container_add(GTK_CONTAINER(alignment), vBox);
	gtk_container_add(GTK_CONTAINER(mWindow), alignment);
	//Some callbacks that need everything to function
	g_signal_connect(entry, "activate", G_CALLBACK(newbill_add_item), &eData);
	g_signal_connect(entry1, "changed", G_CALLBACK(newbill_entry_changed), &eData);
	g_signal_connect(list1, "row-activated", G_CALLBACK(newbill_entry_add), &eData);

	gtk_widget_show_all(mWindow);

	return 0;
}

void newbill_init_list1(GtkWidget *list)	{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("S.No", renderer, "text", 0, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 50);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Item ID", renderer, "text", 1, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 150);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Item Name", renderer, "text", 2, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 150);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Quantity", renderer, "text", 3, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 100);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Cost", renderer, "text", 4, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 100);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	store = gtk_list_store_new(5, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT);
	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	g_object_unref(store);
}

void newbill_init_list2(GtkWidget *list)	{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Suggestions", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	store = gtk_list_store_new(1, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

	g_object_unref(store);
}