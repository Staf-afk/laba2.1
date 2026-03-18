#ifndef STUDENT_H
#define STUDENT_H

#include "passport.h"

typedef struct {
    char* firstName;
    char* secondName;
    char* lastName;
    int dayStudentBirth;
    int monthStudentBirth;
    int yearStudentBirth;
    Person_ID id;
    int scholarship;
} Student;

typedef struct {
    Student* data;
    int size;
} StudentArray;

void initStudentList(StudentArray* arr);
void addStudent(StudentArray* arr, char* firstName, char* secondName, char* lastName,
                int dayStudentBirth, int monthStudentBirth, int yearStudentBirth,
                Student_ID* ID, int scholarship);
void removeStudent(StudentArray* arr, int index);
void freeStudentArray(StudentArray* arr);
void printStudent(Student* s);
void printAllStudents(StudentArray* arr);

#endif