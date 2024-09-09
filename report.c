#include "report.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swapStudents(Student *a, Student *b) {
    int tempReg = a->registration;
    char tempName[100];
    char tempCourse[50];
    strcpy(tempName, a->name);
    strcpy(tempCourse, a->course);
    int tempYear = a->entryYear;
    float *tempGrades = a->grades;
    int *tempAttendance = a->attendance;

    a->registration = b->registration;
    strcpy(a->name, b->name);
    strcpy(a->course, b->course);
    a->entryYear = b->entryYear;
    a->grades = b->grades;
    a->attendance = b->attendance;

    b->registration = tempReg;
    strcpy(b->name, tempName);
    strcpy(b->course, tempCourse);
    b->entryYear = tempYear;
    b->grades = tempGrades;
    b->attendance = tempAttendance;
}

//n² sort
void sortStudentsByRegistration(Student **list) {
    if (*list == NULL) return;

    int swapped;
    Student* ptr1;
    Student* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *list;

        while (ptr1->next != lptr) {
            if (ptr1->registration > ptr1->next->registration) {
                swapStudents(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

Student* sortedMerge(Student *a, Student *b, int (*compare)(Student*, Student*)) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (compare(a, b) <= 0) {
        a->next = sortedMerge(a->next, b, compare);
        return a;
    } else {
        b->next = sortedMerge(a, b->next, compare);
        return b;
    }
}

void splitList(Student *source, Student **front, Student **back) {
    if (source == NULL || source->next == NULL) {
        *front = source;
        *back = NULL;
        return;
    }

    Student *slow = source;
    Student *fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

//n log n sort
void mergeSort(Student **list, int (*compare)(Student*, Student*)) {
    if (*list == NULL || (*list)->next == NULL) return;

    Student *a, *b;

    splitList(*list, &a, &b);

    mergeSort(&a, compare);
    mergeSort(&b, compare);

    *list = sortedMerge(a, b, compare);
}

int compareTotalGrades(Student *a, Student *b) {
    float totalA = 0, totalB = 0;
    for (int i = 0; a->grades[i] != -1; i++) totalA += a->grades[i];
    for (int i = 0; b->grades[i] != -1; i++) totalB += b->grades[i];
    return totalB - totalA;
}

int compareAbsences(Student *a, Student *b) {
    int absencesA = 0, absencesB = 0;
    for (int i = 0; i < 18; i++) {
        if (a->attendance[i] == 0) absencesA++;
        if (b->attendance[i] == 0) absencesB++;
    }
    return absencesB - absencesA;
}

Student* copyStudentList(Student *list) {
    if (list == NULL) return NULL;

    Student *newList = NULL, *last = NULL;

    while (list != NULL) {
        Student *newStudent = (Student*)malloc(sizeof(Student));

        newStudent->registration = list->registration;
        strcpy(newStudent->name, list->name);
        strcpy(newStudent->course, list->course);
        newStudent->entryYear = list->entryYear;

        newStudent->grades = (float*)malloc(100 * sizeof(float));  // Supondo que o array de grades tem até 100 elementos
        newStudent->attendance = (int*)malloc(18 * sizeof(int));   // 18 elementos de attendance
        memcpy(newStudent->grades, list->grades, 100 * sizeof(float));
        memcpy(newStudent->attendance, list->attendance, 18 * sizeof(int));

        newStudent->next = NULL;

        if (newList == NULL) {
            newList = newStudent;
            last = newStudent;
        } else {
            last->next = newStudent;
            last = newStudent;
        }

        list = list->next;
    }

    return newList;
}

void generateStudentReport(Student *list) {
    if (list == NULL) {
        printf("\nNo registered students.\n\n");
        sleep(3);
        return;
    }

    Student *copiedList = copyStudentList(list);  // Copia a lista antes de ordenar

    int choice;
    printf("\e[1;1H\e[2J");
    printf("Sort by:\n");
    printf("1. Number of Absences\n");
    printf("2. Total Grades\n");
    printf("3. Registration Number\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            mergeSort(&copiedList, compareAbsences);
            break;
        case 2:
            mergeSort(&copiedList, compareTotalGrades);
            break;
        case 3:
            // Ordenação por número de registro será feita pelo Bubble Sort original
            sortStudentsByRegistration(&copiedList);
            break;
        default:
            printf("Invalid option. Sorting by registration number.\n");
            sortStudentsByRegistration(&copiedList);
            break;
    }

    printStudentReport(copiedList);

    Student *tmp;
    while (copiedList != NULL) {
        tmp = copiedList;
        copiedList = copiedList->next;
        free(tmp->grades); 
        free(tmp->attendance); 
        free(tmp);
    }
}

void printStudentReport(Student *list) {
    Student *current = list;

    while (current != NULL) {
        float totalGrades = 0;
        int absences = 0;

        for (int i = 0; current->grades[i] != -1; i++) {
            totalGrades += current->grades[i];
        }

        for (int i = 0; i < 18; i++) {
            if (current->attendance[i] == 0) absences++;
        }

        printf("Registration: %d, Name: %s, Total Grades: %.2f, Absences: %d\n",
               current->registration, current->name, totalGrades, absences);

        if (absences >= 10) {
            printf("\nStudent failed due to absences.\n");
        }

        sleep(3);
        current = current->next;
    }
}
