#include <gtk/gtk.h>

enum
{
  LIST_ITEM = 0,
  N_COLUMNS
};

int main(int argc, char *argv[])	{
	GtkWidget *mainWindow;
	GtkWidget *hBox;
	GtkWidget *vBox;
	GtkWidget *list;
	GtkWidget *entry;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *scrollWindow;

	//These are some stuff for the tree view init part
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;

	//We initiate the gtk
	gtk_init(&argc, &argv);
	//We create the mainWindow as a Toplevel window
	mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mainWindow), "Inventory");
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 600, 600);
	gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(mainWindow), 10);
	g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//We create the vBox for alignment purposes
	vBox = gtk_vbox_new(TRUE, 10);
	//Now we set up a temprary hBox for alignment of stuff
	hBox = gtk_hbox_new(FALSE, 10);
	label = gtk_label_new("Enter Product Name :");
	gtk_widget_set_size_request(label, 125, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry, 150, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);
	label= gtk_label_new("Qty");
	gtk_widget_set_size_request(label, 100, 30);
	gtk_box_pack_start(GTK_BOX(hBox), label, 0, 0, 0);
	entry = gtk_entry_new();
	gtk_widget_set_size_request(entry, 150, 30);
	gtk_box_pack_start(GTK_BOX(hBox), entry, 0, 0, 0);

	//We add the hBox to the vBox;
	gtk_box_pack_start(GTK_BOX(vBox), hBox, 0, 0, 0);
	//We now create the list inside of a scroll window
	scrollWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrollWindow), GTK_SHADOW_ETCHED_IN);
	list = gtk_tree_view_new();
	//We Initialize tree view with 5 columns and also set the size of the columns
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("S.No", renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 50);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Item ID", renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 150);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Item Name", renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 150);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Stock", renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 100);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	column = gtk_tree_view_column_new_with_attributes("Price", renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width(column, 100);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	store = gtk_list_store_new(5, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT);
	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	g_object_unref(store);
	gtk_container_add(GTK_CONTAINER(scrollWindow), list);
	gtk_box_pack_start(GTK_BOX(vBox), scrollWindow, 0, 0, 0);
	//We add the vBox to the container
	gtk_container_add(GTK_CONTAINER(mainWindow), vBox);

	gtk_widget_show_all(mainWindow);

	gtk_main();

	return 0;
}