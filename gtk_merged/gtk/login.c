extern GtkWidget *mWindow;

void login_screen()	{
	GtkWidget *entry1, *entry2;
	GtkWidget *label;
	GtkWidget *vbox, *hBox;
	GtkWidget *valign;
	GtkWidget *button;
	static struct _login_myEntries ent;
	//We Set up the initial window which acts as the main window
	mWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mWindow), "Login");
	gtk_window_set_position(GTK_WINDOW(mWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(mWindow), 300, 300);
	gtk_window_set_resizable(GTK_WINDOW(mWindow), FALSE);
	ent.exitCallId = g_signal_connect(mWindow, "destroy", G_CALLBACK(gtk_package_exit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(mWindow), 15);

	vbox = gtk_vbox_new(TRUE, 10);
	//For the username and the text entry
	hBox = gtk_hbox_new(FALSE, 5);
	label = gtk_label_new("Username");
	gtk_widget_set_size_request(label, 70, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0 , 0);
	entry1 = gtk_entry_new();
	gtk_widget_set_size_request(entry1, 130, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry1, 0 , 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hBox, 0, 0 , 0);
	//For the password and its entry feild
	hBox = gtk_hbox_new(FALSE , 5);
	label= gtk_label_new("Password");
	gtk_widget_set_size_request(label, 70, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry2 = gtk_entry_new();
	gtk_widget_set_size_request(entry2, 130, 30);
	gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
	gtk_box_pack_start(GTK_BOX(hBox), entry2, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hBox, 0, 0 ,10);
	//Now for the login button
	hBox = gtk_hbox_new(FALSE, 5);
	button = gtk_button_new_with_label("Login");
	gtk_widget_set_size_request(button, 90, 40);
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);

	ent.entryName = entry1;
	ent.entryPass = entry2;
	//We set the temp to pass the data over to the callback function
	g_signal_connect(button, "clicked", G_CALLBACK(login_user), &ent);
	//We put the vbox in a alignment that is kept at the center of the window all the time
	valign = gtk_alignment_new(0.50, 0.50, 0, 0);
	gtk_container_add(GTK_CONTAINER(valign), vbox);
	gtk_container_add(GTK_CONTAINER(mWindow), valign);
	gtk_widget_show_all(mWindow);
}
