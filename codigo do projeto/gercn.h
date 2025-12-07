G_MODULE_EXPORT void criar_conta()
{
    const char *nus = gtk_entry_get_text(Ent_NUsr);
    const int npin = atoi(gtk_entry_get_text(Ent_NUPin));
    add_user(nus, npin);

}

G_MODULE_EXPORT void mudar_pin()
{
    const int apin = atoi(gtk_entry_get_text(Ent_APin));
    const int npin = atoi(gtk_entry_get_text(Ent_NPin));
    if(apin == pinAtual && usrAtual > -1){
        usuarios[usrAtual].pin = npin;
    }
    return;
}



G_MODULE_EXPORT void gerenciar_contas()
{
    gtk_widget_show(JanelaGerenciamento);
}

gboolean on_gercn_del(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_widget_hide(JanelaGerenciamento);
    return TRUE;
}
