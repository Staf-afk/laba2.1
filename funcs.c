#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

typedef enum{
    TYPE_STUDENT = 1,
    TYPE_TEACHER = 2
} PersonType;

int addPrefixToStudentName(Student* s) {
    if (!s || !s->firstName) return 0;
    char* newFirst = malloc(strlen(s->firstName) + 4);
    if (!newFirst) return 0;
    sprintf(newFirst, "[префикс] %s", s->firstName);
    free(s->firstName);
    s->firstName = newFirst;
    return 1;
}

int addPrefixToTeacherName(Teacher* t) {
    if (!t || !t->firstName) return 0;
    char* newFirst = malloc(strlen(t->firstName) + 4);
    if (!newFirst) return 0;
    sprintf(newFirst, "[префикс] %s", t->firstName);
    free(t->firstName);
    t->firstName = newFirst;
    return 1;
}

StudentArray* mapStudents(StudentArray* arr, int (*mapper)(Student*)) {
    if (!arr || !mapper) return NULL;
    StudentArray* result = malloc(sizeof(StudentArray));
    if (!result) return NULL;
    initStudentList(result);
    if (arr->size > 0) {
        result->data = malloc(arr->size * sizeof(Student));
        if (!result->data) { free(result); return NULL; }
    } else {
        result->data = NULL;
    }
    for (int i = 0; i < arr->size; i++) {
        result->data[i] = arr->data[i];
        result->data[i].firstName = strdup(arr->data[i].firstName);
        result->data[i].secondName = strdup(arr->data[i].secondName);
        result->data[i].lastName = strdup(arr->data[i].lastName);
        mapper(&result->data[i]);
    }
    result->size = arr->size;
    return result;
}

TeacherArray* mapTeachers(TeacherArray* arr, int (*mapper)(Teacher*)) {
    if (!arr || !mapper) return NULL;
    TeacherArray* result = malloc(sizeof(TeacherArray));
    if (!result) return NULL;
    initTeacherList(result);
    if (arr->size > 0) {
        result->data = malloc(arr->size * sizeof(Teacher));
        if (!result->data) { free(result); return NULL; }
    } else {
        result->data = NULL;
    }
    for (int i = 0; i < arr->size; i++) {
        result->data[i] = arr->data[i];
        result->data[i].firstName = strdup(arr->data[i].firstName);
        result->data[i].secondName = strdup(arr->data[i].secondName);
        result->data[i].lastName = strdup(arr->data[i].lastName);
        mapper(&result->data[i]);
    }
    result->size = arr->size;
    return result;
}

void concatPrint(StudentArray* students, TeacherArray* teachers) {
    printf("\n  === ОБЪЕДИНЁННЫЙ СПИСОК ===\n");
    int total = 0;
    if (students && students->size > 0) {
        printf("  -- Студенты (%d):\n", students->size);
        printAllStudents(students);
        total += students->size;
    }
    if (teachers && teachers->size > 0) {
        printf("  -- Преподаватели (%d):\n", teachers->size);
        printAllTeachers(teachers);
        total += teachers->size;
    }
    if (total == 0) printf("  (списки пусты)\n");
    else printf("  Итого: %d человек\n", total);
}

Student* findStudentByID(StudentArray* arr, int series, int number) {
    if (!arr || arr->data == NULL) return NULL;
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i].id.series == series && arr->data[i].id.number == number) {
            return &arr->data[i];
        }
    }
    return NULL;  
}

Teacher* findTeacherByID(TeacherArray* arr, int series, int number) {
    if (!arr || arr->data == NULL) return NULL;
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i].id.series == series && 
            arr->data[i].id.number == number) {
            return &arr->data[i];
        }
    }
    return NULL;
}

void findPersonByID(StudentArray* students, TeacherArray* teachers, int series, int number){
    Student* s = findStudentByID(students, series, number);
    Teacher* t = findTeacherByID(teachers, series, number);
    
    if (s) {
        printf("Найден студент:\n");
        printStudent(s);
    } else if (t) {
        printf("Найден преподаватель:\n");
        printTeacher(t);
    } else {
        printf("Человек с таким паспортом не найден.\n");
    }
}