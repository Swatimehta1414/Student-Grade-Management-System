// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_GRADES 5

typedef struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    float grades[MAX_GRADES];
    int numGrades;
    float gpa;
} Student;

typedef struct StudentNode {
    Student data;
    struct StudentNode* next;
} StudentNode;

void displayTitleScreen();
void readCSV(StudentNode** head);
void writeCSV(StudentNode* head);
void showMenu();
void addStudent(StudentNode** head);
void visualizeGPA(StudentNode* head); 
void displayStudents(StudentNode* head);
void modifyStudent(StudentNode* head, int id);
float calculateGPA(float grades[], int numGrades);
StudentNode* sortedMerge(StudentNode* a, StudentNode* b, int criteria);
void frontBackSplit(StudentNode* listHead, StudentNode** frontRef, StudentNode** backRef);
void sortStudents(StudentNode** headRef, int criteria);
Student* searchStudent(StudentNode* head, int id);
void deleteStudent(StudentNode** head, int id);
void displayTable(StudentNode* head);
void calculateStudentEfficiency(StudentNode* head);
void printCourseBarChart(Student student);
void freeStudentList(StudentNode** head);

#endif
