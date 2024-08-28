#ifndef STUDENT_H
#define STUDENT_H

#include "hash_table.h"

typedef struct Student {
    int registration;
    char name[100];
    char course[50];
    int entryYear;
    float *grades;
    int *attendance;
    struct Student *next;
} Student;

void initializeStudent(Student *student);
void registerStudent(HashTable *hashTable, Student **list);
void freeMemory(Student **list);

#endif
