#include "evaluation.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void registerEvaluation(Student *list) {
    int totalStudents = 0;
    Student *current = list;
    while (current != NULL) {
        totalStudents++;
        current = current->next;
    }

    if (totalStudents == 0) {
        printf("No students registered.\n");
        return;
    }

    float *grades = (float*)malloc(totalStudents * sizeof(float));
    int i = 0;
    current = list;
    while (current != NULL) {
        printf("\e[1;1H\e[2J");
        printf("Grade for student %s: ", current->name);
        scanf("%f", &grades[i]);
        i++;
        current = current->next;
    }

    i = 0;
    current = list;
    while (current != NULL) {
        int gradeCount = 0;
        while (current->grades != NULL && current->grades[gradeCount] != -1) {
            gradeCount++;
        }

        if (gradeCount == 0) {
            current->grades = (float*)malloc(2 * sizeof(float));
        } else {
            current->grades = (float*)realloc(current->grades, (gradeCount + 2) * sizeof(float));
        }
        current->grades[gradeCount] = grades[i];
        current->grades[gradeCount + 1] = -1;

        i++;
        current = current->next;
    }

    printf("Grades registered successfully!\n");
}

void generateGradeReport(Student *list) {
    int totalStudents = 0;
    Student *current = list;
    while (current != NULL) {
        totalStudents++;
        current = current->next;
    }

    if (totalStudents == 0) {
        printf("No students registered.\n");
        return;
    }

    float maxGrade = -1, minGrade = 101, gradeSum = 0;
    int totalGrades = 0;

    current = list;
    while (current != NULL) {
        if (current->grades != NULL) {
            for (int i = 0; current->grades[i] != -1; i++) {
                if (current->grades[i] > maxGrade) maxGrade = current->grades[i];
                if (current->grades[i] < minGrade) minGrade = current->grades[i];
                gradeSum += current->grades[i];
                totalGrades++;
            }
        }
        current = current->next;
    }

    float averageGrade = gradeSum / totalGrades;
    printf("Max Grade: %.2f, Min Grade: %.2f, Average Grade: %.2f\n", maxGrade, minGrade, averageGrade);

    float *grades = (float*)malloc(totalGrades * sizeof(float));
    int i = 0;
    current = list;
    while (current != NULL) {
        if (current->grades != NULL) {
            for (int j = 0; current->grades[j] != -1; j++) {
                grades[i++] = current->grades[j];
            }
        }
        current = current->next;
    }

    //Sort grades in descending order
    for (int i = 0; i < totalGrades - 1; i++) {
        for (int j = i + 1; j < totalGrades; j++) {
            if (grades[i] < grades[j]) {
                float temp = grades[i];
                grades[i] = grades[j];
                grades[j] = temp;
            }
        }
    }

    printf("Grades in descending order:\n");
    for (int i = 0; i < totalGrades; i++) {
        printf("%.2f ", grades[i]);
    }
    printf("\n");

    sleep(5);

}
