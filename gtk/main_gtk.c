#include <gtk/gtk.h>
struct _labelData	{
	GtkWidget *entryMessage, *entryStatistics;
};

static void new_bill(GtkWidget *widget, struct _labelData *data);
static void show_inv(GtkWidget *widget, struct _labelData *data);
static void check_inv(GtkWidget *widget, struct _labelData *data);
static void new_item(GtkWidget *widget, struct _labelData *data);
static void config(GtkWidget *widget, struct _labelData *data);
static void exit_event(GtkWidget *widget);

int main(int argc, char *argv[])	{
	GtkWidget *window;
	GtkWidget *hBox, *vBoxMain, *vBoxTemp;
	GtkWidget *button;
	GtkWidget *entry;;
	char *temp;
	struct _labelData EData;

	gtk_init(&argc, &argv);

	//We start with the main window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Main");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

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
	g_signal_connect(button, "clicked", G_CALLBACK(exit_event), NULL);
	gtk_box_pack_start(GTK_BOX(hBox), button, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(vBoxMain), hBox, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(window), vBoxMain);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

static void new_bill(GtkWidget *widget, struct _labelData *data)	{
	g_print("New Bill Is Called.\n");
}
static void show_inv(GtkWidget *widget, struct _labelData *data)	{
	g_print("Show Inventory is Called.\n");
}
static void check_inv(GtkWidget *widget, struct _labelData *data)	{
	g_print("Check Inventory is Called.\n");
}
static void new_item(GtkWidget *widget, struct _labelData *data)	{
	g_print("New Item is Called.\n");
}
static void config(GtkWidget *widget, struct _labelData *data)	{
	g_print("Config is Called.\n");
}
static void exit_event(GtkWidget *widget)	{
	g_print("Exit is Called.\n");
}