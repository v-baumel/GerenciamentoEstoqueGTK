
gboolean fechar_mod(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_widget_hide(JanelaModificar);
    return TRUE;
}

G_MODULE_EXPORT void mod_open()
{
    gtk_widget_show(JanelaModificar);
    gtk_window_set_keep_above(GTK_WINDOW(JanelaModificar), TRUE);
}


G_MODULE_EXPORT void click_mod()
{
    if(linha_selecionada > -1){
        Item novoItem;
        strcpy(novoItem.tipo , gte(M_Ti));
        strcpy(novoItem.marca , gte(M_Ma));
        strcpy(novoItem.modelo , gte(M_Mo));
        strcpy(novoItem.descricao , gte(M_De));
        strcpy(novoItem.novo , gte(M_No));
        strcpy(novoItem.num_serie , gte(M_NS));
        strcpy(novoItem.num_patrimonio , gte(M_NP));
        strcpy(novoItem.alocacao , gte(M_Al));
        strcpy(novoItem.status , gte(M_St));
        modificarItem(novoItem);

    }
}

