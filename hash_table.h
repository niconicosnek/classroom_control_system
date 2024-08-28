#ifndef HASH_TABLE_H
#define HASH_TABLE_H

//#include "student.h"

typedef struct Student Student;

typedef struct HashTable {
    Student *table[100];
} HashTable;

void initializeHashTable(HashTable *hashTable);
int hash(int registration);

#endif
