
gboolean fechar_add(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_widget_hide(JanelaAdicionar);
    return TRUE;
}

G_MODULE_EXPORT void add_open()
{
    gtk_widget_show(JanelaAdicionar);
    gtk_window_set_keep_above(GTK_WINDOW(JanelaAdicionar), TRUE);
}

G_MODULE_EXPORT void click_add()
{
    Item novoItem;
    strcpy(novoItem.tipo , gte(A_Ti));
    strcpy(novoItem.marca , gte(A_Ma));
    strcpy(novoItem.modelo , gte(A_Mo));
    strcpy(novoItem.descricao , gte(A_De));
    strcpy(novoItem.novo , gte(A_No));
    strcpy(novoItem.num_serie , gte(A_NS));
    strcpy(novoItem.num_patrimonio , gte(A_NP));
    strcpy(novoItem.alocacao , gte(A_Al));
    strcpy(novoItem.status , gte(A_St));
    cadastrarItem(novoItem);
}
