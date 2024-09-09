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
    int evaluation;
    int i = 0;
    current = list;

    printf("\e[1;1H\e[2J");
    printf("Evaluation number: ");
    scanf("%d", &evaluation);

    while (current != NULL) {
        printf("\e[1;1H\e[2J");
        printf("------ P%d ------\n", evaluation);
        printf("Grade for student %s: ", current->name);
        scanf("%f", &grades[i]);
        i++;
        current = current->next;
    }

    i = 0;
    current = list;
    while (current != NULL) {
        current->grades = (float*)realloc(current->grades, (evaluation + 2) * sizeof(float));
        
        for (int j = 0; j <= evaluation; j++) {
            if (j != evaluation && current->grades[j] == -1) {
                current->grades[j] = 0; //Assuming each non registered grade is 0.
            }
        }

        current->grades[evaluation] = grades[i];
        current->grades[evaluation + 1] = -1;

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
        printf("\nNo student registered.\n\n");
        sleep(3);
        return;
    }

    if(list->grades == NULL ) {
        printf("\nNo grade registered.\n\n");
        sleep(3);
        return;
    }

    float maxGrade = -1, minGrade = 101, gradeSum = 0;
    int totalGrades = 0, evaluation = 0;

    printf("\e[1;1H\e[2J");
    printf("Evaluation number: ");
    scanf("%d", &evaluation);

    current = list;
    while (current != NULL) {
        if (current->grades != NULL && current->grades[evaluation] != -1) {
            if (current->grades[evaluation] > maxGrade) maxGrade = current->grades[evaluation];
            if (current->grades[evaluation] < minGrade) minGrade = current->grades[evaluation];
            gradeSum += current->grades[evaluation];
            totalGrades++;
        }
        current = current->next;
    }

    float averageGrade = gradeSum / totalGrades;
    printf("------ P%d ------\n", evaluation);
    printf("Max Grade: %.2f, Min Grade: %.2f, Average Grade: %.2f\n", maxGrade, minGrade, averageGrade);

    float *grades = (float*)malloc(totalGrades * sizeof(float));
    int i = 0;
    current = list;
    while (current != NULL) {
        if (current->grades != NULL && current->grades[evaluation] != -1) {
            grades[i++] = current->grades[evaluation];
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
