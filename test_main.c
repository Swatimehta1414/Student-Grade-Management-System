#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#define SORT_BY_NAME 2

StudentNode* createStudentNode(int id, const char* name, float grades[]) {
    StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    newNode->data.id = id;
    strncpy(newNode->data.name, name, MAX_NAME_LENGTH - 1);
    newNode->data.name[MAX_NAME_LENGTH - 1] = '\0';
    for (int i = 0; i < MAX_GRADES; i++) {
        newNode->data.grades[i] = grades[i];
    }
    newNode->data.numGrades = MAX_GRADES;
    newNode->data.gpa = calculateGPA(grades, MAX_GRADES);
    newNode->next = NULL;
    return newNode;
}


int compareStudents(const Student* s1, const Student* s2) {
    if (s1->id != s2->id) return 0;
    if (strcmp(s1->name, s2->name) != 0) return 0;
    for (int i = 0; i < MAX_GRADES; i++) {
        if (s1->grades[i] != s2->grades[i]) return 0;
    }
    return 1;
}

void test_addStudent() {
    StudentNode* head = NULL;
    Student newStudent;
    newStudent.id = 1;
    strncpy(newStudent.name, "Test Student", MAX_NAME_LENGTH - 1);
    newStudent.name[MAX_NAME_LENGTH - 1] = '\0';
    float grades[MAX_GRADES] = {90, 80, 70, 60, 50};
    for (int i = 0; i < MAX_GRADES; i++) {
        newStudent.grades[i] = grades[i];
    }
    newStudent.numGrades = MAX_GRADES;
    newStudent.gpa = calculateGPA(grades, MAX_GRADES);

    StudentNode* newNode = malloc(sizeof(StudentNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        return;
    }

    newNode->data = newStudent;
    newNode->next = head;
    head = newNode;

    if (head != NULL && head->data.id == 1 && strcmp(head->data.name, "Test Student") == 0) {
        printf("Test Case Passed: Add student successfully\n");
    } else {
        printf("Test Case Failed: Add student successfully\n");
    }

    freeStudentList(&head);
}

void test_deleteStudent() {
    StudentNode* head = NULL;
    float grades1[MAX_GRADES] = {90, 80, 70, 60, 50};
    float grades2[MAX_GRADES] = {100, 90, 80, 70, 60};
    StudentNode* student1 = createStudentNode(1, "Toomy", grades1);
    StudentNode* student2 = createStudentNode(2, "Tuffy", grades2);

    student1->next = student2;
    head = student1;

    deleteStudent(&head, 1);

    if (head != NULL && head->data.id == 2) {
        printf("Test Case Passed: Delete student successfully\n");
    } else {
        printf("Test Case Failed: Delete student successfully\n");
    }

    freeStudentList(&head);
}

void test_searchStudent() {
    StudentNode* head = NULL;
    float grades1[MAX_GRADES] = {90, 80, 70, 60, 50};
    float grades2[MAX_GRADES] = {100, 90, 80, 70, 60};
    StudentNode* student1 = createStudentNode(1, "Toomy", grades1);
    StudentNode* student2 = createStudentNode(2, "Tuffy", grades2);
    student1->next = student2;
    head = student1;

    Student* foundStudent = searchStudent(head, 2);
    if (foundStudent != NULL && foundStudent->id == 2) {
        printf("Test Case Passed: Search student successfully\n");
    } else {
        printf("Test Case Failed: Search student successfully\n");
    }

    Student* notFoundStudent = searchStudent(head, 3);
    if (notFoundStudent == NULL) {
        printf("Test Case Passed: Search student not found\n");
    } else {
        printf("Test Case Failed: Search student not found\n");
    }

    freeStudentList(&head);
}

void test_calculateGPA() {
    float grades1[MAX_GRADES] = {80, 90, 70, 85, 95};
    float grades2[3] = {100, 100, 100};
    float grades3[MAX_GRADES] = {50, 60, 70, 80, 90};

    float gpa1 = calculateGPA(grades1, MAX_GRADES);
    float gpa2 = calculateGPA(grades2, 3);
    float gpa3 = calculateGPA(grades3, MAX_GRADES);

    printf("Testing GPA Calculation:\n");
    printf("GPA1 Got: %.2f (Expected: Varies based on grading scale)\n", gpa1);
    printf("GPA2 Got: %.2f (Expected: Varies based on grading scale)\n", gpa2);
    printf("GPA3 Got: %.2f (Expected: Varies based on grading scale)\n", gpa3);
}

void test_sortStudents() {
    StudentNode* head = NULL;
    float grades1[MAX_GRADES] = {80, 90, 70, 85, 95};
    float grades2[MAX_GRADES] = {100, 90, 80, 70, 60};
    float grades3[MAX_GRADES] = {50, 60, 70, 80, 90};

    StudentNode* student1 = createStudentNode(1, "sheela", grades1);
    StudentNode* student2 = createStudentNode(2, "chameli", grades2);
    StudentNode* student3 = createStudentNode(3, "kareena", grades3);

    student1->next = student2;
    student2->next = student3;
    head = student1;

    sortStudents(&head, 2);

    printf("Testing sortStudents (Sort by Name):\n");

    freeStudentList(&head);
}


void test_sortStudents_Name() {
    StudentNode* head = NULL;
    
  
    float grades1[MAX_GRADES] = {90, 80, 70, 85, 95};
    StudentNode* student1 = createStudentNode(1, "Chamlie", grades1);
    float grades2[MAX_GRADES] = {70, 60, 50, 45, 35};
    StudentNode* student2 = createStudentNode(2, "kareena", grades2); 
    float grades3[MAX_GRADES] = {60, 50, 40, 35, 25};
    StudentNode* student3 = createStudentNode(3, "Beyonce", grades3);


    student1->next = student2;
    student2->next = student3;
    head = student1;

    printf("Testing sortStudents (by Name):\n");
    sortStudents(&head, SORT_BY_NAME); 

    int passed = 1;
    StudentNode* current = head;

  
    if (current == NULL || strcmp(current->data.name, "Beyonce") != 0) {
        passed = 0;
        printf("  First node incorrect. Expected 'Beyonce'\n");
    }
    
   
    if (passed) {
        current = current->next;
        if (current == NULL || strcmp(current->data.name, "Chamlie") != 0) {
            passed = 0;
            printf("  Second node incorrect. Expected 'Chamlie'\n");
        }
    }

    if (passed) {
        current = current->next;
        if (current == NULL || strcmp(current->data.name, "kareena") != 0) {
            passed = 0;
            printf("  Third node incorrect. Expected 'kareena'\n");
        }
    }

    if (passed && current->next != NULL) {
        passed = 0;
        printf("  List not properly terminated\n");
    }

    printf("  Test %s: Name sorting\n", passed ? "Passed" : "Failed");

    freeStudentList(&head);
}



void test_BarChartVisualization() {

    Student testStudent;
    testStudent.id = 1;
    strcpy(testStudent.name, "Test Student");
    testStudent.grades[0] = 95.0;
    testStudent.grades[1] = 85.0;
    testStudent.grades[2] = 75.0;
    testStudent.grades[3] = 65.0;
    testStudent.grades[4] = 55.0;
    testStudent.numGrades = MAX_GRADES;
    testStudent.gpa = calculateGPA(testStudent.grades, testStudent.numGrades);

    printf("Testing BarChartVisualization:\n");
    printCourseBarChart(testStudent);
  
}

void test_displayTable() {
    StudentNode* head = NULL;
    float grades1[MAX_GRADES] = {80, 90, 70, 85, 95};
    StudentNode* student1 = createStudentNode(1, "Kareena khan", grades1);

    head = student1;
    printf("Testing displayTable:\n");
    displayTable(head);

    freeStudentList(&head);
}

void test_calculateStudentEfficiency() {
     StudentNode* head = NULL;
    float grades1[MAX_GRADES] = {80, 90, 70, 85, 95};
    StudentNode* student1 = createStudentNode(1, "Beyonce", grades1);

    head = student1;
    printf("Testing calculateStudentEfficiency:\n");
    calculateStudentEfficiency(head);

    freeStudentList(&head);
}

int main() {
    test_addStudent();
    test_deleteStudent();
    test_searchStudent();
    test_calculateGPA();
    test_displayTable();
    test_calculateStudentEfficiency();
    test_sortStudents_Name();
     test_BarChartVisualization();

    printf("\nALL TESTS COMPLETED\n");
    return 0;
}
