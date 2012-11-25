extern GtkWidget *mWindow;
extern WindowDetails cWindowDetails;

int gtk_main_page()	{
	GtkWidget *window;
	GtkWidget *hBox, *vBoxMain, *vBoxTemp;
	GtkWidget *button;
	GtkWidget *entry;;
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
	entry = gtk_entry_new();
	EData.entryMessage = entry;
	gtk_widget_set_size_request(entry, 350, 225);
	gtk_entry_set_editable(GTK_ENTRY(entry), FALSE);
	//@TODO set the initial messages here @ entry
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
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
	entry = gtk_entry_new();
	EData.entryStatistics = entry;
	gtk_widget_set_size_request(entry, 350, 225);
	gtk_entry_set_editable(GTK_ENTRY(entry), FALSE);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
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
	button = gtk_button_new_with_label("Configuration");
	gtk_widget_set_size_request(button, 200, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(config), &EData);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	button = gtk_button_new_with_label("Exit");
	gtk_widget_set_size_request(button, 200, 50);
	g_signal_connect(button, "clicked", G_CALLBACK(gtk_package_exit), NULL);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBoxMain), hBox, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(mWindow), vBoxMain);
	gtk_widget_show_all(mWindow);
	return 0;
}