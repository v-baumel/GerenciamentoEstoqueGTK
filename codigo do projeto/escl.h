
gboolean fechar_escl(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_widget_hide(JanelaEscolher);
    return TRUE;
}

G_MODULE_EXPORT void escl_open()
{
    gtk_widget_show(JanelaEscolher);
    gtk_window_set_keep_above(GTK_WINDOW(JanelaEscolher), TRUE);
}

void criar_escolhedor(){
    Escolhedor = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(Escolhedor), TRUE);

    // Add a file filter for .csv files
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "CSV files");
    gtk_file_filter_add_pattern(filter, "*.csv");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(Escolhedor), filter);

    gtk_container_add(GTK_CONTAINER(JanelaEscolher), Escolhedor);
    gtk_widget_show(Escolhedor);
}

void on_file_selected(GtkFileChooser *file_chooser, gpointer user_data) {
    atualizarTudo();
    gtk_widget_hide(JanelaEscolher);
}
