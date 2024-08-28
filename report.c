#include "report.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//n² sort (Bubble Sort)
void sortStudentsByRegistration(Student **list) {
    if (*list == NULL) return;

    int swapped;
    Student *ptr1;
    Student *prev1;
    Student *prev2;
    Student *next;

    do {
        swapped = 0;
        prev1 = NULL;
        ptr1 = *list;

        while (ptr1->next != NULL) {
            next = ptr1->next;
            if (ptr1->registration > next->registration) {
                if (prev1 == NULL) {
                    *list = next;
                } else {
                    prev1->next = next;
                }

                ptr1->next = next->next;
                next->next = ptr1;

                swapped = 1;

                prev2 = next;
            } else {
                prev2 = ptr1;
            }

            prev1 = prev2;
            ptr1 = prev2->next;
        }
    } while (swapped);
}




//n log n sort (Merge Sort)
Student* sortedMerge(Student *a, Student *b, int (*compare)(Student*, Student*)) {
    Student *result = NULL;

    if (a == NULL) return b;
    if (b == NULL) return a;

    if (compare(a, b) <= 0) {
        result = a;
        result->next = sortedMerge(a->next, b, compare);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next, compare);
    }
    return result;
}

void splitList(Student *source, Student **front, Student **back) {
    Student *fast;
    Student *slow;
    slow = source;
    fast = source->next;

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

void mergeSort(Student **list, int (*compare)(Student*, Student*)) {
    Student *head = *list;
    Student *a;
    Student *b;

    if ((head == NULL) || (head->next == NULL)) return;

    splitList(head, &a, &b);

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

void sortStudentsByTotalGrades(Student **list) {
    mergeSort(list, compareTotalGrades);
}

void sortStudentsByAbsences(Student **list) {
    mergeSort(list, compareAbsences);
}

void generateStudentReport(Student *list) {
    if(list->grades == NULL ) {
        printf("\nNo registered grade.\n\n");
        sleep(3);
        return;
    }

    int choice;
    printf("Sort by:\n");
    printf("1. Registration Number\n");
    printf("2. Total Grades\n");
    printf("3. Number of Absences\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sortStudentsByRegistration(&list);
            break;
        case 2:
            sortStudentsByTotalGrades(&list);
            break;
        case 3:
            sortStudentsByAbsences(&list);
            break;
        default:
            printf("Invalid option. Sorting by registration number.\n");
            sortStudentsByRegistration(&list);
            break;
    }

    printStudentReport(list);
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
        sleep(3);
        current = current->next;
    }
}
