//This file is only for including and documenting the other GTK files.
//First we add the structs required for data transfer from one callback to the other
#include "gtk_callback_structs.h"
//Secondly we add all the callback functions so it wont cause some missing func declarations
#include "gtk_callbacks.h"
//We first include the login screen.
#include "login.c"
//Then we include the main gtk method.
#include "main_gtk.c"
//new item page
#include "newitem.c"
//Search Page
#include "search.c"
//New bill page
//#include "newbill.c"