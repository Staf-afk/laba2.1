#ifndef FUNCS_H
#define FUNCS_H

#include "student.h"
#include "teacher.h"

typedef struct {
    int series;
    int number;
} Person_ID;

int addPrefixToStudentName(Student* s);
int addPrefixToTeacherName(Teacher* t);

Teacher* findTeacherByID(TeacherArray* arr, int series, int number);
Student* findStudentByID(StudentArray* arr, int series, int number);

StudentArray* mapStudents(StudentArray* arr, int (*mapper)(Student*));
TeacherArray* mapTeachers(TeacherArray* arr, int (*mapper)(Teacher*));
void concatPrint(StudentArray* students, TeacherArray* teachers);
void findPersonByID(StudentArray* students, TeacherArray* teachers, int series, int number);
#endif