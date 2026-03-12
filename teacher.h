#ifndef TEACHER_H
#define TEACHER_H

#include <time.h>

typedef struct {
    int series;
    int number;
} Teacher_ID;

typedef struct{
    Teacher_ID id;
    char* firstName;
    char* secondName;
    char* lastName;
    time_t dateBirth;
    int salary;
} Teacher;

typedef struct{
    Teacher* data;
    int size;
} TeacherArray;

void initTeacherList(TeacherArray* arr);
void addTeacher(TeacherArray* arr, char* firstName,
                char* secondName, char* lastName,
                time_t dateBirth, Teacher_ID* ID,
                int salary);
void removeTeacher(TeacherArray* arr, int index);
void freeTeacherArray(TeacherArray* arr);
void printTeacher(Teacher* t);
void printAllTeachers(TeacherArray* arr);

#endif