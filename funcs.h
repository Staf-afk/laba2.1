#ifndef FUNCS_H
#define FUNCS_H

#include "student.h"
#include "teacher.h"

int addPrefixToStudentName(Student* s);
int addPrefixToTeacherName(Teacher* t);
StudentArray* mapStudents(StudentArray* arr, int (*mapper)(Student*));
TeacherArray* mapTeachers(TeacherArray* arr, int (*mapper)(Teacher*));
void concatPrint(StudentArray* students, TeacherArray* teachers);
Student* findStudentByID(StudentArray* arr, int series, int number);
Teacher* findTeacherByID(TeacherArray* arr, int series, int number);
void findPersonByID(StudentArray* students, TeacherArray* teachers, int series, int number);

#endif