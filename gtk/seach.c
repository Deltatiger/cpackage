#include <gtk/gtk.h>

# define IS_CHAR(x) ( (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
# define IS_NUM(x) ((x >= '0' && x <= '9'))

enum	{
	LIST_ITEM = 0,
	N_COLUMNS
};

struct _searchEntryData	{
	GtkWidget *entry;
	GtkWidget *label;
};

GtkWidget *list;

static void init_list(GtkWidget *list)	{
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

static void add_to_list(GtkWidget *list, const gchar *str)	{
	GtkListStore *store;
	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

void print(GtkWidget *widget, struct _searchEntryData *data)	{
	const gchar *text;
	int flag = 0,i;
	text = gtk_entry_get_text(GTK_ENTRY(data->entry));
	for(i= 0; text[i] != '\0'; i++)	{
		if(i == 0)	{
			if(IS_CHAR(text[i]))	{
				flag = -1;
			} else if(IS_NUM(text[i]))	{
				flag = 1;
			}
		} else {
			if((IS_CHAR(text[i]) && flag != -1) || (IS_NUM(text[i]) && flag != 1))	{
				//This is an error as the charecter types dont match.
				gtk_label_set_text(GTK_LABEL(data->label), "Error. Not a valid ID or Name.");
				return;
			}
		}
	}
}

int main(int argc, char *argv[])	{
	GtkWidget *window;
	GtkWidget *label, *entry;
	GtkWidget *button;
	GtkWidget *align;
	GtkWidget *vBox;
	GtkWidget *temp;
	GtkWidget *selection;
	struct _searchEntryData data;

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
	data.entry = entry;
	gtk_widget_set_size_request(entry, 150, 30);
	gtk_box_pack_start(GTK_BOX(temp), entry, 0 , 0 , 0);
	gtk_box_pack_start(GTK_BOX(vBox), temp, 0, 0 ,0);

	button = gtk_button_new_with_label("Submit");
	gtk_box_pack_start(GTK_BOX(vBox), button, 0, 0,0);

	list = gtk_tree_view_new();
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);
	gtk_box_pack_start(GTK_BOX(vBox), list, 0, 0 , 0);

	init_list(list);
	gtk_widget_set_size_request(list, 100, 150);

	label = gtk_label_new("Test");
	data.label = label;
	gtk_widget_set_size_request(label, 200, 300);
	gtk_box_pack_start(GTK_BOX(vBox), label, 0, 0, 0);

	align = gtk_alignment_new(0.50, 0.50, 0, 0);
	gtk_container_add(GTK_CONTAINER(align), vBox);
	gtk_container_add(GTK_CONTAINER(window), align);

	g_signal_connect(entry, "changed", G_CALLBACK(print), &data);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}