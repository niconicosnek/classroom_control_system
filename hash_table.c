#include "hash_table.h"
#include <stddef.h>

void initializeHashTable(HashTable *hashTable) {
    for (int i = 0; i < 100; i++) {
        hashTable->table[i] = NULL;
    }
}

int hash(int registration) {
    return registration % 100;
}
