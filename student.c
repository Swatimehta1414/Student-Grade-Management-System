// student.c
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

const char* courseCodes[MAX_GRADES] = {"CS2043", "CS2263", "CS2253", "CS2613", "CS2614"};

int getPadding(int consoleWidth, const char* text) {
    int textLength = strlen(text);
    return (consoleWidth - textLength) / 2;
}

void displayTitleScreen() {
    int consoleWidth = 70;
    int topPadding = getPadding(consoleWidth, "============================================");
    for (int i = 0; i < topPadding; i++) printf(" ");
    printf("============================================\n");
    int projectNamePadding = getPadding(consoleWidth, "CS2263 Project: Student_Management_System");
    for (int i = 0; i < projectNamePadding; i++) printf(" ");
    printf("2263 Project: Student_Management_System\n");
    int authorsPadding = getPadding(consoleWidth, "MADE BY Divyanshi, Muhammad Jahanzib, Swati Mehta");
    for (int i = 0; i < authorsPadding; i++) printf(" ");
    printf("MADE BY DIVYANSHI, Muhammad Jahanzib, Swati Mehta\n");
    int bottomPadding = getPadding(consoleWidth, "============================================");
    for (int i = 0; i < bottomPadding; i++) printf(" ");
    printf("============================================\n");
    int promptPadding = getPadding(consoleWidth, "Press any key to continue...");
    for (int i = 0; i < promptPadding; i++) printf(" ");
    printf("Press any key to continue...\n");
    getchar();
}

void readCSV(StudentNode** head) {
    FILE* file = fopen("students.csv", "r");
    if (file == NULL) {
        printf("students.csv not found. Creating a new file\n");
        file = fopen("students.csv", "w");
        if (file == NULL) {
            printf("Error: Could not create students.csv.\n");
            return;
        }
        fclose(file);
        return;
    }

    Student student;
    while (fscanf(file, "%d,%49[^,],%f,%f,%f,%f,%f\n",
                  &student.id, student.name,
                  &student.grades[0], &student.grades[1],
                  &student.grades[2], &student.grades[3],
                  &student.grades[4]) == 7) {
        student.numGrades = 5;
        student.gpa = calculateGPA(student.grades, student.numGrades);
        StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));
        if (node == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }
        node->data = student;
        node->next = *head;
        *head = node;
    }
    fclose(file);
}
void writeCSV(StudentNode* head) {
    FILE *file = fopen("students.csv", "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    StudentNode* current = head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f\n", current->data.id, current->data.name,
                current->data.grades[0], current->data.grades[1], current->data.grades[2],
                current->data.grades[3], current->data.grades[4]);
        current = current->next;
    }
    fclose(file);
}

void showMenu() {
    printf("\n======== MENU ========\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Delete Student\n");
    printf("4. Table Visualization\n");
    printf("5. Bar Chart Visualization\n");
    printf("6. Sort Students\n");
    printf("7. Search Student\n");
    printf("8. Modify Student\n");
    printf("9. Calculate Student Efficiency\n");
    printf("10. Exit\n");
    printf("======================\n");
    printf("Enter your choice: ");
}

void addStudent(StudentNode** head) {
    Student newStudent;
    printf("Enter Student ID: ");
    scanf("%d", &newStudent.id);

    // we have created this method to check for duplicate ID and prompt an error message on invaild input
    for (StudentNode* temp = *head; temp != NULL; temp = temp->next) {
        if (temp->data.id == newStudent.id) {
            printf("Error: Student with ID %d already exists.\n", newStudent.id);
            return;
        }
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Enter Student Name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    size_t len = strlen(newStudent.name);
    if (len > 0 && newStudent.name[len - 1] == '\n') {
        newStudent.name[len - 1] = '\0';
    }

    printf("Enter grades for the following courses:\n");
    newStudent.numGrades = 0;
    for (int i = 0; i < MAX_GRADES; i++) {
        newStudent.grades[i] = 0.0; // Ensure grades are initialized
        printf("%s: ", courseCodes[i]);
        if (scanf("%f", &newStudent.grades[i]) == 1) {
            newStudent.numGrades++;
        } else {
            printf("Invalid input. Grade set to 0.\n");
            newStudent.grades[i] = 0;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }

    newStudent.gpa = calculateGPA(newStudent.grades, newStudent.numGrades);
    StudentNode* newNode = malloc(sizeof(StudentNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        return;
    }

    newNode->data = newStudent;
    newNode->next = *head;
    *head = newNode;
    printf("Student added successfully.\n");
    writeCSV(*head);
}

void visualizeGPA(StudentNode* head) {
    if (head == NULL) {
        printf("No students to display GPA visualization.\n");
        return;
    }

    printf("\n*******GPA Visualization********\n");
    for (StudentNode* ptr = head; ptr != NULL; ptr = ptr->next) {
        printf("Student: %s (ID: %d), GPA: %.2f\n", ptr->data.name, ptr->data.id, ptr->data.gpa);
        const char* barColor;
        if (ptr->data.gpa >= 4.0) {
            barColor = GRN;
        } else if (ptr->data.gpa >= 3.0) {
            barColor = BLU;
        } else if (ptr->data.gpa >= 2.0) {
            barColor = YEL;
        } else {
            barColor = RED;
        }

        int barLength = (int)(ptr->data.gpa * 5);
        printf("GPA: %s", barColor);
        for (int i = 0; i < barLength; ++i) {
            putchar('#');
        }
        printf(RESET "\n");
    }
}

void displayStudents(StudentNode* head) {
    if (head == NULL) {
        printf("No data.\n");
        return;
    }

    printf("\n********* Students List ***********\n");
    StudentNode* current = head;
    while (current != NULL) {
        printf("STUDENT ID: %d, Name: %s, GPA: %.2f\n", current->data.id, current->data.name, current->data.gpa);
        current = current->next;
    }
}


void modifyStudent(StudentNode* head, int id) {
    StudentNode* current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            printf("Student found. Enter new grades for the following courses:\n");
            for (int j = 0; j < MAX_GRADES; j++) {
                printf("%s: ", courseCodes[j]);
                if (scanf("%f", &current->data.grades[j]) == 1) {
                    current->data.numGrades = MAX_GRADES;
                } else {
                    printf("Invalid input. Keeping old grade.\n");
                    while (getchar() != '\n');
                }
            }
            current->data.gpa = calculateGPA(current->data.grades, current->data.numGrades);
            printf("Student information is updated now ! \n");
            writeCSV(head);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found.\n", id);
}

float calculateGPA(float grades[], int numGrades) {
    if (numGrades == 0) return 0.0;
    float sum = 0;
    for (int i = 0; i < numGrades; i++) {
        float gradePoint;
        if (grades[i] >= 90) {
            gradePoint = 4.3;
        } else if (grades[i] >= 85) {
            gradePoint = 4.0;
        } else if (grades[i] >= 80) {
            gradePoint = 3.7;
        } else if (grades[i] >= 75) {
            gradePoint = 3.3;
        } else if (grades[i] >= 70) {
            gradePoint = 3.0;
        } else if (grades[i] >= 65) {
            gradePoint = 2.7;
        } else if (grades[i] >= 60) {
            gradePoint = 2.3;
        } else if (grades[i] >= 50) {
            gradePoint = 2.0;
        } else if (grades[i] >= 45) {
            gradePoint = 1.7;
        } else if (grades[i] >= 40) {
            gradePoint = 1.3;
        } else if (grades[i] >= 35) {
            gradePoint = 1.0;
        } else if (grades[i] >= 30) {
            gradePoint = 0.7;
        } else {
            gradePoint = 0.0;
        }
        sum += gradePoint;
    }
    return sum / numGrades;
}

StudentNode* sortedMerge(StudentNode* a, StudentNode* b, int criteria) {
    StudentNode* result = NULL;
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    switch (criteria) {
        case 1:
            if (a->data.id <= b->data.id) {
                result = a;
                result->next = sortedMerge(a->next, b, criteria);
            } else {
                result = b;
                result->next = sortedMerge(a, b->next, criteria);
            }
            break;
        case 2:
            if (strcmp(a->data.name, b->data.name) <= 0) {
                result = a;
                result->next = sortedMerge(a->next, b, criteria);
            } else {
                result = b;
                result->next = sortedMerge(a, b->next, criteria);
            }
            break;
        case 3:
            if (a->data.gpa >= b->data.gpa) {
                result = a;
                result->next = sortedMerge(a->next, b, criteria);
            } else {
                result = b;
                result->next = sortedMerge(a, b->next, criteria);
            }
            break;
        default:
            return NULL;
    }
    return result;
}

void frontBackSplit(StudentNode* listHead, StudentNode** frontRef, StudentNode** backRef) {
    StudentNode* fast;
    StudentNode* slow;
    if (listHead == NULL || listHead->next == NULL) {
        *frontRef = listHead;
        *backRef = NULL;
        return;
    }

    slow = listHead;
    fast = listHead->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = listHead;
    *backRef = slow->next;
    slow->next = NULL;
}

void sortStudents(StudentNode** headRef, int criteria) {
    StudentNode* head = *headRef;
    StudentNode* a;
    StudentNode* b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    frontBackSplit(head, &a, &b);
    sortStudents(&a, criteria);
    sortStudents(&b, criteria);
    *headRef = sortedMerge(a, b, criteria);
}

Student* searchStudent(StudentNode* head, int id) {
    StudentNode* current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            return &(current->data);
        }
        current = current->next;
    }
    return NULL;
}

void deleteStudent(StudentNode** head, int id) {
    StudentNode* current = *head;
    StudentNode* prev = NULL;
    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Student with ID %d deleted successfully.\n", id);
    writeCSV(*head);
}

void displayTable(StudentNode* head) {
    if (head == NULL) {
        printf("No students to display.\n");
        return;
    }

    printf("\n+-------+----------------------+-------+\n");
    printf("|  ID   |         Name         |  GPA  |\n");
    printf("+-------+----------------------+-------+\n");
    StudentNode* current = head;
    while (current != NULL) {
        printf("| %5d | %-20s | %5.2f |\n", current->data.id, current->data.name, current->data.gpa);
        current = current->next;
    }
    printf("+-------+----------------------+-------+\n");
}

void calculateStudentEfficiency(StudentNode* head) {
    printf("\n--- Student Efficiency Based on GPA ---\n");
    StudentNode* current = head;
    while (current != NULL) {
        printf("Student: %s (ID: %d)\n", current->data.name, current->data.id);
        printf("GPA: %.2f\n", current->data.gpa);
        if (current->data.gpa >= 4.3) {
            printf("Efficiency: Outstanding\n");
        } else if (current->data.gpa >= 4.0) {
            printf("Efficiency: Excellent\n");
        } else if (current->data.gpa >= 3.7) {
            printf("Efficiency: Very Good\n");
        } else if (current->data.gpa >= 3.3) {
            printf("Efficiency: Good\n");
        } else if (current->data.gpa >= 3.0) {
            printf("Efficiency: Satisfactory\n");
        } else if (current->data.gpa >= 2.7) {
            printf("Efficiency: Average\n");
        } else if (current->data.gpa >= 2.3) {
            printf("Efficiency: Below Average\n");
        } else if (current->data.gpa >= 2.0) {
            printf("Efficiency: Poor\n");
        } else {
            printf("Efficiency: Unsatisfactory\n");
        }
        printf("\n");
        current = current->next;
    }
}

void printCourseBarChart(Student student) {
    const int MAX_BAR_LENGTH = 20;
    printf("Student: %s (ID: %d)\n", student.name, student.id);
    for (int i = 0; i < MAX_GRADES; i++) {
        int barLength = (int)((student.grades[i] / 100.0) * MAX_BAR_LENGTH);
        printf("%s | ", courseCodes[i]);
        const char* color;
        if (student.grades[i] >= 90) {
            color = GRN;
        } else if (student.grades[i] >= 80) {
            color = BLU;
        } else if (student.grades[i] >= 70) {
            color = CYN;
        } else if (student.grades[i] >= 60) {
            color = YEL;
        } else {
            color = RED;
        }
        printf("%s", color);
        for (int j = 0; j < barLength; j++) {
            printf("#");
        }
        printf("%s", RESET);
        for (int j = barLength; j < MAX_BAR_LENGTH; j++) {
            printf(" ");
        }
        printf("| (%.0f)\n", student.grades[i]);
    }
    printf("\n");
}

void freeStudentList(StudentNode** head) {
    StudentNode* current = *head;
    StudentNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
    printf("Wow memory Freed is successfull.\n");
}
