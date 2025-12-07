
gboolean fechar_filtro(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_widget_hide(JanelaFiltros);
    return TRUE;
}

G_MODULE_EXPORT void abrir_filtros()
{
    gtk_widget_show(JanelaFiltros);
    gtk_window_set_keep_above(GTK_WINDOW(JanelaFiltros), TRUE);
}


int checarLinha(int x){
    for(int i = 0; i < 9; i++){
        char *flt = filtros[i];
        if(strncmp(flt, pegarValorStruct(x, i+1), strlen(flt))!=0) return 0;
    }
    return 1;
}

void aplicarFiltros(){
    for(int i = 1; i < vecInv.size; i++){
        if(checarLinha(i)==0){
            gtk_widget_hide(vector_get(&vecInv, i)->linha);
        }  else {
            gtk_widget_show(vector_get(&vecInv, i)->linha);
        }
    }
    return;
}



G_MODULE_EXPORT void click_filtros()
{
    strcpy(filtros[0], gte(F_Ti));
    strcpy(filtros[1], gte(F_Ma));
    strcpy(filtros[2], gte(F_Mo));
    strcpy(filtros[3], gte(F_De));
    strcpy(filtros[4], gte(F_No));
    strcpy(filtros[5], gte(F_NS));
    strcpy(filtros[6], gte(F_NP));
    strcpy(filtros[7], gte(F_Al));
    strcpy(filtros[8], gte(F_St));
    aplicarFiltros();
}
