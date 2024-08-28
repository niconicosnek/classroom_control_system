#ifndef REPORT_H
#define REPORT_H

#include "student.h"

void generateStudentReport(Student *list);
void printStudentReport(Student *list);
void sortStudentsByRegistration(Student **list);
void sortStudentsByTotalGrades(Student **list);
void sortStudentsByAbsences(Student **list);

#endif
