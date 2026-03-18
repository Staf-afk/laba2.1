#ifndef TEACHER_H
#define TEACHER_H

#include "passport.h"

typedef struct {
    char* firstName;
    char* secondName;
    char* lastName;
    int dayTeacherBirth;
    int monthTeacherBirth;
    int yearTeacherBirth;
    Person_ID id;
    int salary;
} Teacher;

typedef struct {
    Teacher* data;
    int size;
} TeacherArray;

void initTeacherList(TeacherArray* arr);
void addTeacher(TeacherArray* arr, char* firstName, char* secondName, char* lastName,
                int dayTeacherBirth, int monthTeacherBirth, int yearTeacherBirth,
                Teacher_ID* ID, int salary);
void removeTeacher(TeacherArray* arr, int index);
void freeTeacherArray(TeacherArray* arr);
void printTeacher(Teacher* t);
void printAllTeachers(TeacherArray* arr);

#endif