#include "attendance.h"
#include <stdio.h>

void recordAttendance(Student *list) {
    int day;
    printf("\e[1;1H\e[2J");
    printf("Enter the day of attendance (1-18): ");
    scanf("%d", &day);
    if (day < 1 || day > 18) {
        printf("Invalid day.\n");
        return;
    }
    day -= 1;  // Adjust to index from 0 to 17

    Student *current = list;
    while (current != NULL) {
        printf("\e[1;1H\e[2J");
        printf("Is student %s present? (1 for yes, 0 for no): ", current->name);
        int attendance;
        scanf("%d", &attendance);
        current->attendance[day] = attendance;

        int absences = 0;
        for (int i = 0; i < 18; i++) {
            if (current->attendance[i] == 0) {
                absences++;
            }
        }
        if (absences >= 10) {
            printf("Student %s failed due to absence.\n", current->name);
        }

        current = current->next;
    }
}
