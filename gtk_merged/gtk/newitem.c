extern GtkWidget *mWindow;

int gtk_newitem_page()	{
	GtkWidget *vBox, *hBox;
	GtkWidget *entry;
	GtkWidget *label;
	GtkWidget *alignment;
	GtkWidget *button;
	struct _newItem_entryIds entries;

	mWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mWindow), "New Item");
	gtk_window_set_default_size(GTK_WINDOW(mWindow), 300, 300);
	gtk_window_set_position(GTK_WINDOW(mWindow), GTK_WIN_POS_CENTER);
	g_signal_connect(mWindow, "destroy", G_CALLBACK(gtk_sub_window_quit), NULL);

	//We start adding stuff to the vBox via the hBox
	vBox = gtk_vbox_new(TRUE, 5);

	hBox = gtk_hbox_new(FALSE, 5);
	label = gtk_label_new("Item Name");
	gtk_widget_set_size_request(label, 70, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0 ,0);

	entry = gtk_entry_new();
	entries.entry1 = entry;
	gtk_widget_set_size_request(entry, 140, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 5);

	//Now for item cost
	hBox = gtk_hbox_new(FALSE, 5);
	label = gtk_label_new("Item Price");
	gtk_widget_set_size_request(label, 70, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0 ,0);

	entry = gtk_entry_new();
	entries.entry2 = entry;
	gtk_widget_set_size_request(entry, 140, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 5);

	//And now for the initial stock
	hBox = gtk_hbox_new(FALSE, 5);
	label = gtk_label_new("Initial Stock");
	gtk_widget_set_size_request(label, 70, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0 ,0);

	entry = gtk_entry_new();
	entries.entry3 = entry;
	g_print("%p", entry);
	gtk_widget_set_size_request(entry, 140, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 5);
	//And now for the button
	button = gtk_button_new_with_label("Done");
	gtk_widget_set_size_request(button, 130, 30);
	g_signal_connect(button, "clicked", G_CALLBACK(new_item_entry), &entries);
	gtk_box_pack_start(GTK_BOX(vBox), button, 0, 0, 5);
	//Now that we got the vBox all ready lets put it up in the halignment
	alignment = gtk_alignment_new(0.5 , 0.5, 0, 0);
	gtk_container_add(GTK_CONTAINER(alignment), vBox);
	gtk_container_add(GTK_CONTAINER(mWindow), alignment);
	gtk_widget_show_all(mWindow);
	return 0;
}
