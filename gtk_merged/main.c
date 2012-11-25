#include "package_headers.h"

GtkWidget *mWindow;
WindowDetails cWindowDetails;
int loginStat = 0;

int main(int argc, char *argv[])	{
	gtk_init(&argc, &argv);
	cWindowDetails.activeWindow = NULL;
	cWindowDetails.hiddenWindow = NULL;
	package_init(&gInit);
	login_screen();
	gtk_main();
	return 0;
}