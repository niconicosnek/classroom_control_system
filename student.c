#include "student.h"
// #include <windows.h> // 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeStudent(Student *student) {
    student->grades = NULL;
    student->attendance = (int*)calloc(18, sizeof(int));  // Initialize with 18 classes
    student->next = NULL;
}

void registerStudent(HashTable *hashTable, Student **list) {
    Student *newStudent = (Student*)malloc(sizeof(Student));
    initializeStudent(newStudent);

    printf("\e[1;1H\e[2J");
    printf("Registration: ");
    scanf("%d", &newStudent->registration);
    printf("Name: ");
    scanf(" %[^\n]", newStudent->name);
    printf("Course: ");
    scanf(" %[^\n]", newStudent->course);
    printf("Year of Entry: ");
    scanf("%d", &newStudent->entryYear);

    //Add to the linked list
    newStudent->next = *list;
    *list = newStudent;

    //Update the hash table
    int index = hash(newStudent->registration);
    hashTable->table[index] = newStudent;

    printf("Student registered successfully!\n");
    sleep(1);

}

void freeMemory(Student **list) {
    Student *current = *list;
    while (current != NULL) {
        Student *temp = current;
        current = current->next;
        free(temp->grades);
        free(temp->attendance);
        free(temp);
    }
    *list = NULL;
}
