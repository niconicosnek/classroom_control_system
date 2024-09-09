#ifndef REPORT_H
#define REPORT_H

#include "student.h"

void generateStudentReport(Student *list);
void printStudentReport(Student *list);
void sortStudentsByRegistration(Student **list);
void sortStudentsByTotalGrades(Student **list);
void sortStudentsByAbsences(Student **list);
Student* copyStudentList(Student *list);
int compareAbsences(Student *a, Student *b);
int compareTotalGrades(Student *a, Student *b);

#endif
