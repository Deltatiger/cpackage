//This function holds all the gtk_callback declarations ands their defs are in gtk_callbacks.c
#ifndef	_gtk_callbacks_h
	#define _gtk_callbacks_h
	//All the declarations go here. We add them with comments so that they work properly.
	//login callbacks
	static void login_user(GtkWidget *widget, struct _login_myEntries *entry);
	void gtk_package_exit(GtkWidget *widget, gpointer data);
	//main_gtk callbacks
	static void new_bill(GtkWidget *widget, struct _mainGtk_labelData *data);
	static void show_inv(GtkWidget *widget, struct _mainGtk_labelData *data);
	static void check_inv(GtkWidget *widget, struct _mainGtk_labelData *data);
	static void new_item(GtkWidget *widget, struct _mainGtk_labelData *data);
	static void config(GtkWidget *widget, struct _mainGtk_labelData *data);
	//New item callbacks
	static void new_item_entry(GtkWidget *widget, gpointer data);
	//Search Item Callbacks
	static void add_to_list(GtkWidget *list, const gchar *str);
	void search_item_check(GtkWidget *widget, gpointer data);
	//General Callbacks
	static void exit_event(GtkWidget *widget);
	#include "gtk_callbacks.c"
#endif