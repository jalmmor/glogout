#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>


void ev_cancelar(GtkWidget *widget, gpointer window){
	gtk_main_quit();	
}

void ev_reiniciar(GtkWidget *widget, gpointer window){
	system("systemctl reboot && openbox --exit");
	gtk_main_quit();

}

void ev_apagar(GtkWidget *widget, gpointer window){
  system("systemctl poweroff && openbox --exit");
	gtk_main_quit();

}

void ev_cerrar(GtkWidget *widget, gpointer window){
  system("openbox --exit");
	gtk_main_quit();
}

static GtkWidget* createWindow(){


	GtkWidget *window;
	GtkWidget *table;

	GtkWidget *Cancelar;
	GtkWidget *Reiniciar;
	GtkWidget *Apagar;
	GtkWidget *Cerrar;
	
	 GtkAccelGroup *accel;

	//gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        accel = gtk_accel_group_new ();
	gtk_window_add_accel_group (GTK_WINDOW (window), accel);
	table = gtk_table_new(1, 4, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 2);
	gtk_table_set_col_spacings(GTK_TABLE(table), 2);

	Cancelar = gtk_button_new_with_mnemonic("Cancelar");
	gtk_widget_add_accelerator (Cancelar, "clicked", accel,   GDK_KEY_Escape, 0, GTK_ACCEL_VISIBLE);
	
	Reiniciar = gtk_button_new_with_mnemonic("_Reiniciar");
	gtk_widget_add_accelerator (Reiniciar, "clicked", accel,   GDK_KEY_r, 0, GTK_ACCEL_VISIBLE);

	Apagar = gtk_button_new_with_mnemonic("_Apagar");
	gtk_widget_add_accelerator (Apagar, "clicked", accel,   GDK_KEY_a, 0, GTK_ACCEL_VISIBLE);
	
	Cerrar = gtk_button_new_with_mnemonic("_Cerrar sesión");
	gtk_widget_add_accelerator (Cerrar, "clicked", accel,   GDK_KEY_c, 0, GTK_ACCEL_VISIBLE);

	gtk_table_attach(GTK_TABLE(table), Apagar, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), Reiniciar, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), Cancelar, 2, 3, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), Cerrar, 3, 4, 0, 1, GTK_FILL, GTK_FILL, 3, 3);

	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);

	g_signal_connect(G_OBJECT(Cancelar), "clicked", 
	G_CALLBACK(ev_cancelar), (gpointer) window); 


	g_signal_connect(G_OBJECT(Reiniciar), "clicked", 
	G_CALLBACK(ev_reiniciar), (gpointer) window); 

	g_signal_connect(G_OBJECT(Apagar), "clicked", 
	G_CALLBACK(ev_apagar), (gpointer) window); 

	g_signal_connect(G_OBJECT(Cerrar), "clicked", 
	G_CALLBACK(ev_cerrar), (gpointer) window); 

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
	G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	//gtk_widget_show_all(window);

	//gtk_main();

	return window;
}

static void activate (GtkApplication *app) {
	GList *list;
	GtkWidget *window;
	list = gtk_application_get_windows (app);
	if (list){
		//window=GTK_WINDOW (list->data);
		//gtk_window_present (window);
		gtk_main_quit ();
	}
	else {
		window = createWindow ();
		gtk_window_set_application (GTK_WINDOW (window), app);
	}
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 220, 70);
	gtk_window_set_title(GTK_WINDOW(window), "Apagar");
	gtk_window_set_resizable( GTK_WINDOW(window),FALSE);	
	gtk_widget_show_all (GTK_WIDGET (window));
}

int main( int argc, char *argv[]){
	GtkApplication *app;
	gint status;
	app = gtk_application_new ("jam.logout", 0);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION(app), argc, argv);
	g_object_unref (app);
	return status;	
}


