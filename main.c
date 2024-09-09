/* Classroom Management System in C

This practical project was developed for the Algorithms and Data Structures I course at the Federal 
Center for Technological Education Celso Suckow da Fonseca. The project's goal was to create a system 
to manage student information, including registration, grades, and attendance, using data structures 
such as linked lists and hash tables.

The system allows for student registration, attendance tracking, grading, and the generation of reports sorted 
by different criteria. For sorting, Bubble Sort (O(n^2) complexity) and Merge Sort (O(n log n) complexity) 
algorithms were implemented and tested.

Authors: Enzo Basaldella
         Gustavo Kanji
         Nícolas Henriques
*/

#include <stdio.h>
#include <stdlib.h>
//#include <windows.h> //Windows library for sleep() function to work
#include <unistd.h> //Linux version
#include "student.h"
#include "hash_table.h"
#include "evaluation.h"
#include "attendance.h"
#include "report.h"

int main() {
    //Initialization of student list and hash table
    Student *studentList = NULL;
    HashTable hashTable;
    initializeHashTable(&hashTable);

    int choice;
    do {
        printf("\e[1;1H\e[2J");
        printf("\nMenu:\n");
        printf("1. Register new student\n");
        printf("2. Register evaluation\n");
        printf("3. Record attendance\n");
        printf("4. Generate grade report\n");
        printf("5. Generate student report\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerStudent(&hashTable, &studentList);
                break;
            case 2:
                registerEvaluation(studentList);
                break;
            case 3:
                recordAttendance(studentList);
                break;
            case 4:
                generateGradeReport(studentList);
                break;
            case 5:
                generateStudentReport(studentList);
                break;
            case 6:
                printf("\e[1;1H\e[2J");
                printf("Exiting...\n");
                // Free allocated memory
                freeMemory(&studentList);
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
