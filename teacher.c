#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"

void initTeacherList(TeacherArray* arr){
    arr->data = NULL;
    arr->size = 0;
}

void addTeacher(TeacherArray* arr, char* firstName,
                char* secondName, char* lastName,
                int dayTeacherBirth, int monthTeacherBirth, int yearTeacherBirth, Teacher_ID* ID,
                int salary){
    Teacher* newData = (Teacher*)realloc(arr->data, (arr->size + 1) * sizeof(Teacher));
    if (newData == NULL){
        printf("Ошибка выделения памяти.\n");
        return;
    }
    arr->data = newData;

    arr->data[arr->size].firstName = strdup(firstName);
    arr->data[arr->size].secondName = strdup(secondName);
    arr->data[arr->size].lastName = strdup(lastName);
    arr->data[arr->size].dayTeacherBirth = dayTeacherBirth;
    arr->data[arr->size].monthTeacherBirth = monthTeacherBirth;
    arr->data[arr->size].yearTeacherBirth = yearTeacherBirth;
    arr->data[arr->size].id = *ID;
    arr->data[arr->size].salary = salary;

    arr->size++;
}

void removeTeacher(TeacherArray* arr, int index){
    if (index < 0 || index >= arr->size){
        printf("Неверный индекс человека.\n");
        return;
    }
    free(arr->data[index].firstName);
    free(arr->data[index].secondName);
    free(arr->data[index].lastName);
    
    if (arr->size == 1){
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        printf("Последний человек удален. Массив пуст.\n");
        return;
    }
    Teacher* new_data = (Teacher*)malloc((arr->size - 1) * sizeof(Teacher));
    if (new_data == NULL){
        printf("Ошибка выделения памяти при удалении!\n");
        return;
    }
    
    for (int i = 0; i < index; i++){
        new_data[i] = arr->data[i];
    }
    for (int i = index + 1; i < arr->size; i++){
        new_data[i - 1] = arr->data[i];
    }
    
    free(arr->data);
    arr->data = new_data;
    arr->size--;
    printf("Человек с индексом %d удален. Осталось: %d\n", index + 1, arr->size);
}

void freeTeacherArray(TeacherArray* arr) {
    if (arr->data != NULL){
        for (int i = 0; i < arr->size; i++){
            free(arr->data[i].firstName);
            free(arr->data[i].secondName);
            free(arr->data[i].lastName);
        }
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = 0;
}

void printTeacher(Teacher* t) {
    if (!t) return;
    printf("  [Преподаватель] %s %s %s | ЗП: %d | Дата рождения: %d.%d.%d\n",
           t->lastName, t->firstName, t->secondName, t->salary, t->dayTeacherBirth, t->monthTeacherBirth, t->yearTeacherBirth);
}

void printAllTeachers(TeacherArray* arr) {
    if (!arr || arr->size == 0){
        printf("  (список преподавателей пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++){
        printTeacher(&arr->data[i]);
    }
}