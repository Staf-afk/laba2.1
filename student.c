#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

void initStudentList(StudentArray* arr){
    arr->data = NULL;
    arr->size = 0;
}

void addStudent(StudentArray* arr, char* firstName, 
                char* secondName, char* lastName, 
                time_t dateBirth, Student_ID* ID,
                int scholarship){
    Student* newData = (Student*)realloc(arr->data, (arr->size + 1) * sizeof(Student));
    if (newData == NULL){
        printf("Ошибка выделения памяти.\n");
        return;
    }

    arr->data = newData;
    arr->data[arr->size].firstName = strdup(firstName);
    arr->data[arr->size].secondName = strdup(secondName);
    arr->data[arr->size].lastName = strdup(lastName);
    arr->data[arr->size].dateBirth = dateBirth;
    arr->data[arr->size].id = *ID;
    arr->data[arr->size].scholarship = scholarship;
    
    arr->size++;
}

void removeStudent(StudentArray* arr, int index){
    if(index < 0 || index >= arr->size){
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

    Student* new_data = (Student*)malloc((arr->size - 1) * sizeof(Student));
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

void freeStudentArray(StudentArray* arr){
    if (arr->data != NULL) {
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

void printStudent(Student* t) {
    if (!t) return;
    printf("  [Cтудент] %s %s %s | Стипендия: %d | Дата рождения: %ld\n", t->lastName, t->firstName, t->secondName, t->scholarship, (long)t->dateBirth);
}

void printAllStudents(StudentArray* arr) {
    if (!arr || arr->size == 0){
        printf("  (список студентов пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++){
        printStudent(&arr->data[i]);
    }
}

