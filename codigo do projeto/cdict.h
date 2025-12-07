// Define a key-value pair structure
typedef struct {
    GtkWidget* key;  // Use GtkWidget* as the key
    int value;       // The value is now an integer
} DictEntry;

// Define the hash table structure
typedef struct {
    DictEntry** table;  // Array of pointers to key-value pairs
    size_t size;        // Number of buckets
    size_t count;       // Number of elements stored
} Dictionary;

// Hash function for GtkWidget* keys
size_t hash(GtkWidget* key, size_t size) {
    return ((size_t)key) % size;  // Use the pointer's memory address as the hash
}

// Initialize the dictionary
void dict_init(Dictionary* dict, size_t size) {
    dict->size = size;
    dict->count = 0;
    dict->table = (DictEntry**)calloc(size, sizeof(DictEntry*));
    if (!dict->table) {
        printf("Failed to allocate memory for dictionary.\n");
        exit(1);
    }
}

// Insert a key-value pair into the dictionary
void dict_insert(Dictionary* dict, GtkWidget* key, int value) {
    size_t index = hash(key, dict->size);
    size_t original_index = index;

    while (dict->table[index] != NULL) {
        if (dict->table[index]->key == key) {  // Compare pointers directly
            // Key exists; update value
            dict->table[index]->value = value;
            return;
        }
        index = (index + 1) % dict->size;  // Linear probing
        if (index == original_index) {
            printf("Dictionary is full.\n");
            return;
        }
    }

    // Create a new entry
    DictEntry* entry = (DictEntry*)malloc(sizeof(DictEntry));
    entry->key = key;
    entry->value = value;
    dict->table[index] = entry;
    dict->count++;
}

// Retrieve a value by its GtkWidget* key
int* dict_get(Dictionary* dict, GtkWidget* key) {
    size_t index = hash(key, dict->size);
    size_t original_index = index;

    while (dict->table[index] != NULL) {
        if (dict->table[index]->key == key) {  // Compare pointers directly
            return &dict->table[index]->value;
        }
        index = (index + 1) % dict->size;  // Linear probing
        if (index == original_index) break;  // Full circle
    }
    return NULL;  // Key not found
}

// Remove a key-value pair
void dict_remove(Dictionary* dict, GtkWidget* key) {
    size_t index = hash(key, dict->size);
    size_t original_index = index;

    while (dict->table[index] != NULL) {
        if (dict->table[index]->key == key) {
            // Free the entry
            free(dict->table[index]);
            dict->table[index] = NULL;

            // Rehash items in the same cluster
            size_t next_index = (index + 1) % dict->size;
            while (dict->table[next_index] != NULL) {
                DictEntry* entry_to_rehash = dict->table[next_index];
                dict->table[next_index] = NULL;
                dict->count--;
                dict_insert(dict, entry_to_rehash->key, entry_to_rehash->value);
                free(entry_to_rehash);
                next_index = (next_index + 1) % dict->size;
            }

            dict->count--;
            return;
        }
        index = (index + 1) % dict->size;
        if (index == original_index) break;
    }
    printf("Key not found.\n");
}

// Free the dictionary
void dict_free(Dictionary* dict) {
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->table[i] != NULL) {
            free(dict->table[i]);
        }
    }
    free(dict->table);
}
