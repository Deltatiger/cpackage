//This function holds all the gtk_callback declarations ands their defs are in gtk_callbacks.c
#ifndef	_gtk_callbacks_h
	#define _gtk_callbacks_h
	//All the declarations go here. We add them with comments so that they work properly.
	//Some global Callbacks.
	void gtk_package_exit(GtkWidget *widget, gpointer data);
	void gtk_sub_window_quit(GtkWidget *window, gpointer data);
	void quit_sub_window(GtkWidget *window, gpointer data);
	void add_to_list(GtkWidget *list, const gchar *str);
	void remove_all(GtkWidget *list);
	void show_info(GtkWidget *widget, gpointer data);
	void show_error(GtkWidget *widget, gpointer data);
	//login callbacks
	static void login_user(GtkWidget *widget,struct _login_myEntries *entry);
	//main_gtk callbacks
	static void new_bill(GtkWidget *widget, gpointer fData);
	static void show_inv(GtkWidget *widget, gpointer fData);
	static void check_inv(GtkWidget *widget, gpointer fData);
	static void new_item(GtkWidget *widget, gpointer fData);
	//newitem callbacks
	static void new_item_entry(GtkWidget *widget, gpointer data);
	//search Callbacks
	void search_item_check(GtkWidget *widget, gpointer data);
	void search_item_show(GtkWidget *selection, gpointer label);
	void search_mod_entry(GtkWidget *widget, gpointer data);
	void search_item_mod(GtkWidget *widget, gpointer data);
	void search_item_del(GtkWidget *button, gpointer data);
	//newitem Callbacks
	void newbill_entry_changed(GtkWidget *widget, gpointer data);
	void newbill_entry_add(GtkTreeView *treeView, GtkTreePath *path, GtkTreeViewColumn *column ,gpointer data);
	void add_item_to_billList(GtkWidget *list, productList *product, int qty, int itemCount);
	void newbill_add_item(GtkEntry *entry, gpointer data);
	void newbill_done(GtkWidget *widget, gpointer data);
	//main_gtk stuff
	void main_gtk_set_statistics(GtkWidget *list);
	void main_gtk_set_lowstock(GtkWidget *list);
	#include "gtk_callbacks.c"
#endif