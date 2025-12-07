G_MODULE_EXPORT void princ_destroy()
{
    finalizar();
}

G_MODULE_EXPORT void sair_princ()
{
    save_users_to_csv();
    gtk_widget_hide(JanelaPrincipal);
    gtk_widget_show(JanelaLogin);
    pinAtual = -1;
    usrAtual = -1;
}

G_MODULE_EXPORT void salvar_items()
{
    salvarDados(nomeArquivoPlanilha);
}


void on_row_activated(GtkListBox* box, GtkListBoxRow* row, gpointer user_data) {
     int index = gtk_list_box_row_get_index(row);
     linha_selecionada = index+1;
     Item item = *vector_get(&vecInv, index+1);
     gtk_entry_set_text(M_Al, item.alocacao);
     gtk_entry_set_text(M_De, item.descricao);
     gtk_entry_set_text(M_Ma, item.marca);
     gtk_entry_set_text(M_Mo, item.modelo);
     gtk_entry_set_text(M_No, item.novo);
     gtk_entry_set_text(M_NP, item.num_patrimonio);
     gtk_entry_set_text(M_NS, item.num_serie);
     gtk_entry_set_text(M_St, item.status);
     gtk_entry_set_text(M_Ti, item.tipo);

}

GtkWidget* criar_cabecalho(){
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(box, 1280, 40);

    const char *slot_texts[9] = {
        "Tipo",
        "Marca",
        "Modelo",
        "Descricao",
        "Novo",
        "N. Serie",
        "N. Patrimonio Poli-UPE",
        "Alocacao",
        "Status"
    };

    for (int i = 0; i < 9; i++) {
        GtkWidget *label = gtk_label_new(slot_texts[i]);
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
        gtk_widget_set_size_request(label, tamanhos[i], 40);  //
        gtk_widget_show(label);
    }
    gtk_widget_show(box);

    g_signal_connect(Planilha, "row-activated", G_CALLBACK(on_row_activated), NULL);


    return box;
}

G_MODULE_EXPORT void remover_item()
{
    if(linha_selecionada > -1){
        removerItem(linha_selecionada);
    }
}



