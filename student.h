#ifndef STUDENT_H
#define STUDENT_H

typedef struct{
    int series;
    int number;
} Student_ID;

typedef struct{
    Student_ID id;
    char* firstName;
    char* secondName;
    char* lastName;
    int dayStudentBirth;
    int monthStudentBirth;
    int yearStudentBirth;
    int scholarship;
} Student;

typedef struct{
    Student* data;
    int size;
} StudentArray;

void initStudentList(StudentArray* arr);
void addStudent(StudentArray* arr, char* firstName,
                char* secondName, char* lastName,
                int dayStudentBirth, int monthStudentBirth, int yearStudentBirth, Student_ID* ID,
                int scholarship);
void removeStudent(StudentArray* arr, int index);
void freeStudentArray(StudentArray* arr);
void printStudent(Student* s);
void printAllStudents(StudentArray* arr);

#endif