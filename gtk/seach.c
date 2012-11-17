#include <gtk/gtk.h>

enum	{
	LIST_ITEM = 0,
	N_COLUMNS
};

GtkWidget *list;

int main(int argc, char *argv[])	{
	GtkWidget *window;
	GtkWidget *label, *entry;
	GtkWidget *button;
	GtkWidget *align;
	GtkWidget *vBox;
	GtkWidget *temp;
	GtkWidget *selection;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Search");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	vBox = gtk_vbox_new(FALSE, 10);
	temp = gtk_hbox_new(FALSE, 5);
	label = gtk_label_new("Entry Product Name / ID");
	gtk_widget_set_size_request(label, 150, 30);
	gtk_box_pack_start(GTK_BOX(temp), label, 0, 0 ,0);

	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry, 150, 30);
	gtk_box_pack_start(GTK_BOX(temp), entry, 0 , 0 , 0);
	gtk_box_pack_start(GTK_BOX(vBox), temp, 0, 0 ,0);

	button = gtk_button_new_with_label("Submit");
	gtk_box_pack_start(GTK_BOX(vBox), button, 0, 0,0);

	align = gtk_alignment_new(0.50, 0.50, 0, 0);
	gtk_container_add(GTK_CONTAINER(align), vBox);
	gtk_container_add(GTK_CONTAINER(window), align);

	list = gtk_tree_view_new();
	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}