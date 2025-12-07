typedef struct {
    Item* data;
    size_t size;
    size_t capacity;
} Vector;

// Inicializar o vetor
void vector_init(Vector* vec) {
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

// Adicionar elemento ao final do vetor
void vector_push_back(Vector* vec, Item item) {
    if (vec->size == vec->capacity) {
        size_t new_capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
        Item* new_data = (Item*)realloc(vec->data, new_capacity * sizeof(Item));
        if (new_data == NULL) {
            printf("Failed to allocate memory.\n");
            exit(1);
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size] = item;
    vec->size++;
}

// Remover elemento em indice
void vector_remove(Vector* vec, size_t index) {
    if (index >= vec->size) {
        printf("Invalid index.\n");
        return;
    }
    for (size_t i = index; i < vec->size - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->size--;
}

// Pegar elemento em indice
Item* vector_get(Vector* vec, size_t index) {
    if (index >= vec->size) {
        printf("Invalid index.\n");
        return NULL;
    }
    return &vec->data[index];
}

//Limar memoria do vetor
void vector_free(Vector* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}
