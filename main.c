// main.c
#include "student.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    displayTitleScreen();
    StudentNode* head = NULL;
    int choice, id, criteria;
    readCSV(&head);

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                displayStudents(head);
                break;
            case 3:
                printf("Enter Student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(&head, id);
                break;
            case 4:
                displayTable(head);
                break;
            case 5: 
                if (head != NULL) {
                    int barChartChoice;
                    printf("Choose bar chart type:\n");
                    printf("1. By Subject (Course Grades)\n");
                    printf("2. By CGPA (Student GPAs)\n");
                    printf("Enter your choice: ");
                    scanf("%d", &barChartChoice);

                    if (barChartChoice == 1) {
                        printf("Bar Chart Visualization by Subject:\n");
                        StudentNode* current = head;
                        while (current != NULL) {
                            printCourseBarChart(current->data);
                            current = current->next;
                        }
                        
                    } else if (barChartChoice == 2) {
                        printf("Bar Chart Visualization by CGPA:\n");
                        visualizeGPA(head);
                    } else {
                        printf("Invalid bar chart choice.\n");
                    }
                } else {
                    printf("No students to display bar chart.\n");
                }
                break;
            case 6:
                printf("Sort by: 1. ID 2. Name 3. GPA\n");
                printf("Enter choice: ");
                scanf("%d", &criteria);
                sortStudents(&head, criteria);
                break;
            case 7:
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                Student* foundStudent = searchStudent(head, id);
                if (foundStudent) {
                    printf("Student found: ID: %d, Name: %s, GPA: %.2f\n", foundStudent->id, foundStudent->name, foundStudent->gpa);
                } else {
                    printf("Student with ID %d not found.\n", id);
                }
                break;
            case 8:
                printf("Enter Student ID to modify: ");
                scanf("%d", &id);
                modifyStudent(head, id);
                break;
            case 9:
                calculateStudentEfficiency(head);
                break;
            case 10:
                writeCSV(head);
                printf("Exiting program. Data saved.\n");
                freeStudentList(&head);
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
