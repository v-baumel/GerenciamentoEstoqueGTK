#define MAX_USERS 100



char nomeArquivoPlanilha[256] = "";

void remove_line_ending(char *str) {
    if (str != NULL && (str[0] == '\n' || str[0] == '\r')) {
        memmove(str, str + 1, strlen(str));
    }
}

void atualizarArquivo(){
    FILE *file = file = fopen("location.txt", "r");
    if (file == NULL) {
        return;
    }
    if (fgets(nomeArquivoPlanilha, sizeof(nomeArquivoPlanilha), file) == NULL) {
        fclose(file);
        return;
    }
    fclose(file);

    char *newline = strchr(nomeArquivoPlanilha, '\n');
    if (newline) {
        *newline = '\0';
    }

    FILE *csvFile = fopen(nomeArquivoPlanilha, "r");
    if (csvFile == NULL) {
        return;
    }

    // If the .csv file opens successfully, print the path
    fclose(csvFile);

}

void atualizarLocal(const char *newPath) {
    FILE *file = fopen("location.txt", "w");
    if (file == NULL) {
        perror("Error opening location file for writing");
        return;
    }

    if (fprintf(file, "%s", newPath) < 0) {
        perror("Error writing new path to location file");
    } else {
        printf("Successfully updated the path to: %s\n", newPath);
    }

    fclose(file);
}


char *nomeArquivoUSR = "cadUsers.csv";

typedef struct {
    char codigo[9];
    int pin;
} login;

login usuarios[MAX_USERS];
int num_users = 0;

typedef struct {
    char tipo[30];
    char marca[30];
    char modelo[30];
    char descricao[50];
    char novo[20];
    char num_serie[30];
    char num_patrimonio[30];
    char alocacao[30];
    char status[20];
    GtkWidget *linha; //
} Item;


#include "cvec.h"  // para funções com vetores
Vector vecInv;

char filtros[9][256] =  {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
};

void limpar_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int pinAtual = -1;
int usrAtual = -1;
//ele preenche o vetor usuarios
void reg_users(){

    FILE *file = fopen(nomeArquivoUSR, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    while (fscanf(file, "%12[^;];%d", usuarios[num_users].codigo, &usuarios[num_users].pin) == 2) {
        remove_line_ending(usuarios[num_users].codigo);
        num_users++;
    }

    fclose(file);
}

void save_users_to_csv() {
    FILE *file = fopen(nomeArquivoUSR, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(file, "%s;%d\n", usuarios[i].codigo, usuarios[i].pin);
    }

    fclose(file);
}

void add_user(const char *codigo, int pin) {

    strcpy(usuarios[num_users].codigo, codigo);
    usuarios[num_users].pin = pin;
    num_users++;

}



int initLogin(const char loginUser[9],const int pin)
 {

    // Verifica credenciais
    for (int i = 0; i < num_users; i++) {
        if (strcmp(loginUser, usuarios[i].codigo) == 0 && pin == usuarios[i].pin) {
            pinAtual = pin;
            usrAtual = i;
            return 1; // Login bem-sucedido
        }
    }
    // Caso falhe
    return 0;
}




const char* pegarValorStruct(int x, int p){
    switch(p){
        case 1: return vector_get(&vecInv, x)->tipo; break;
        case 2: return  vector_get(&vecInv, x)->marca; break;
        case 3: return  vector_get(&vecInv, x)->modelo; break;
        case 4: return  vector_get(&vecInv, x)->descricao; break;
        case 5: return vector_get(&vecInv, x)->novo; break;
        case 6: return vector_get(&vecInv, x)->num_serie; break;
        case 7: return vector_get(&vecInv, x)->num_patrimonio; break;
        case 8: return vector_get(&vecInv, x)->alocacao; break;
        case 9: return vector_get(&vecInv, x)->status; break;
    }
}

const int tamanhos[9] = {


    100, // tipo
    80, // marca
    160, // modelo
    120, // desc
    80, // novo
    250, // N. Serie
    250, // N. Pat
    120, // Aloc
    120 // Status
}; // soma = 1280




GtkWidget* criar_linha(int x){
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(box, 1280, 40);
    gtk_container_add(GTK_CONTAINER(row), box);
    for (int i = 0; i < 9; i++) {
        const char *texto = pegarValorStruct(x, i+1);
        GtkWidget *label = gtk_label_new(texto);
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
        gtk_widget_set_size_request(label, tamanhos[i], 40);
        gtk_widget_show(label);
    }
    gtk_widget_show(box);
    gtk_widget_show(row);
    gtk_list_box_insert(GTK_LIST_BOX(Planilha), row, -1);
    return row;
}

void carregarDados(const char *nomeArquivo) {


    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo CSV: %s\n",nomeArquivo);
        return;
    }


    // Le o CSV e preenche o inventario
    Item novoItem;
    fscanf(file, "%29[^;];%29[^;];%29[^;];%49[^;];%29[^;];%29[^;];%29[^;];%29[^;];%19[^\n]",
                  novoItem.tipo,
                  novoItem.marca,
                  novoItem.modelo,
                  novoItem.descricao,
                  novoItem.novo,
                  novoItem.num_serie,
                  novoItem.num_patrimonio,
                  novoItem.alocacao,
                  novoItem.status);
    remove_line_ending(novoItem.tipo);
    vector_push_back(&vecInv, novoItem);

    while (fscanf(file, "%29[^;];%29[^;];%29[^;];%49[^;];%29[^;];%29[^;];%29[^;];%29[^;];%19[^\n]",
                  novoItem.tipo,
                  novoItem.marca,
                  novoItem.modelo,
                  novoItem.descricao,
                  novoItem.novo,
                  novoItem.num_serie,
                  novoItem.num_patrimonio,
                  novoItem.alocacao,
                  novoItem.status) == 9) {  // 9 e o numero de propriedades na struct
                      remove_line_ending(novoItem.tipo);
                      vector_push_back(&vecInv, novoItem);
                      vector_get(&vecInv, vecInv.size-1)->linha = criar_linha(vecInv.size-1);

    }

    fclose(file);
}

char* ItemToText(Item item, char* tx){
    strcat(tx,item.tipo); strcat(tx, ";");
    strcat(tx,item.marca); strcat(tx, ";");
    strcat(tx,item.modelo); strcat(tx, ";");
    strcat(tx,item.descricao); strcat(tx, ";");
    strcat(tx,item.novo); strcat(tx, ";");
    strcat(tx,item.num_serie); strcat(tx, ";");
    strcat(tx,item.num_patrimonio); strcat(tx, ";");
    strcat(tx,item.alocacao); strcat(tx, ";");
    strcat(tx,item.status);
}

void cadastrarItem(Item novoItem){
    vector_push_back(&vecInv, novoItem);
    vector_get(&vecInv, vecInv.size-1)->linha = criar_linha(vecInv.size-1);

}

int linha_selecionada = -1;

void removerItem(int pos){
    gtk_widget_destroy(vector_get(&vecInv, pos)->linha);
    vector_remove(&vecInv, pos);
    linha_selecionada = -1;
}

GtkWidget* get_child(GtkWidget *widget) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    if (children != NULL) {
        GtkWidget *child = GTK_WIDGET(children->data);
        g_list_free(children);
        return child;
    }
    return NULL;
}

void modificarItem(Item item){
    int i = linha_selecionada;
    strcpy(vector_get(&vecInv, i)->tipo ,item.tipo);
    strcpy(vector_get(&vecInv, i)->marca ,item.marca);
    strcpy(vector_get(&vecInv, i)->modelo ,item.modelo);
    strcpy(vector_get(&vecInv, i)->descricao ,item.descricao);
    strcpy(vector_get(&vecInv, i)->novo ,item.novo);
    strcpy(vector_get(&vecInv, i)->num_serie ,item.num_serie);
    strcpy(vector_get(&vecInv, i)->num_patrimonio ,item.num_patrimonio);
    strcpy(vector_get(&vecInv, i)->alocacao ,item.alocacao);
    strcpy(vector_get(&vecInv, i)->status ,item.status);

    GtkWidget *box = get_child(vector_get(&vecInv, i)->linha);
    GList *children = gtk_container_get_children(GTK_CONTAINER(box));
    for(int j = 0; j < 9; j++){
        GtkWidget *label = GTK_WIDGET(g_list_nth_data(children, j));
        gtk_label_set_text(GTK_LABEL(label),pegarValorStruct(i, j+1));
    }
}

// Funcao para salvar os dados no arquivo CSV
void salvarDados(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV para escrita.\n");
        return;
    }
    if (ftruncate(fileno(file), 0) != 0) {
        printf("Error na truncação"); // Print an error if truncation fails
        fclose(file);
        return;
    }
    int i;
    for (i = 0; i < vecInv.size; i++) {
        fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                vector_get(&vecInv, i)->tipo,
                vector_get(&vecInv, i)->marca,
                vector_get(&vecInv, i)->modelo,
                vector_get(&vecInv, i)->descricao,
                vector_get(&vecInv, i)->novo,
                vector_get(&vecInv, i)->num_serie,
                vector_get(&vecInv, i)->num_patrimonio,
                vector_get(&vecInv, i)->alocacao,
                vector_get(&vecInv, i)->status);
    }
    fclose(file);
}

void destuirLinhas() {
    GList *children = gtk_container_get_children(GTK_CONTAINER(Planilha));

    // Iterate over the children and destroy each one
    for (GList *iter = children; iter != NULL; iter = g_list_next(iter)) {
        GtkWidget *child = GTK_WIDGET(iter->data);
        gtk_widget_destroy(child); // Destroy the child widget
    }

    g_list_free(children); // Free the list after use
}

void atualizarTudo(){
    salvarDados(nomeArquivoPlanilha);
    destuirLinhas();
    gchar *file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(Escolhedor));
    if (file_path){
        atualizarLocal(file_path);
        atualizarArquivo();
        g_free(file_path);
        vector_free(&vecInv);
        if(nomeArquivoPlanilha== "") return;
        carregarDados(nomeArquivoPlanilha);
    }else{return;}
}


void finalizar(){
    salvarDados(nomeArquivoPlanilha);
    save_users_to_csv();
    gtk_main_quit();
}







