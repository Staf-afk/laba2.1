#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

int addPrefixToPersonName(PersonBase* p){
    if (!p || !p->firstName) return 0;
    char* newFirst = malloc(strlen(p->firstName) + 17);
    if (!newFirst) return 0;
    sprintf(newFirst, "[префикс] %s", p->firstName);
    free(p->firstName);
    p->firstName = newFirst;
    return 1;
}

PersonArray* mapPersons(PersonArray* arr, int (*mapper)(PersonBase*)){
    if (!arr || !mapper) return NULL;
    
    PersonArray* result = malloc(sizeof(PersonArray));
    if (!result) return NULL;
    initPersonList(result);
    
    for (int i = 0; i < arr->size; i++){
        PersonBase* original = arr->data[i];
        PersonBase* copy = NULL;
        
        if (isStudent(original)){
            Student* s = (Student*)original;
            copy = (PersonBase*)createStudent(
                original->firstName, original->secondName, original->lastName,
                original->dayBirth, original->monthBirth, original->yearBirth,
                &original->id, s->scholarship
            );
        }
        else if (isTeacher(original)){
            Teacher* t = (Teacher*)original;
            copy = (PersonBase*)createTeacher(
                original->firstName, original->secondName, original->lastName,
                original->dayBirth, original->monthBirth, original->yearBirth,
                &original->id, t->salary
            );
        }
        
        if (copy){
            mapper(copy);
            addPerson(result, copy);
        }
    }
    
    return result;
}

void concatPrint(PersonArray* persons){
    printf("\n=== ОБЪЕДИНЁННЫЙ СПИСОК ===\n");
    
    if (!persons || persons->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    
    int studentCount = 0, teacherCount = 0;
    
    for (int i = 0; i < persons->size; i++){
        if (isStudent(persons->data[i])) studentCount++;
        else if (isTeacher(persons->data[i])) teacherCount++;
    }
    
    if (studentCount > 0){
        printf("  -- Студенты (%d):\n", studentCount);
        for (int i = 0; i < persons->size; i++){
            if (isStudent(persons->data[i])){
                printPerson(persons->data[i]);
            }
        }
    }
    
    if (teacherCount > 0){
        printf("  -- Преподаватели (%d):\n", teacherCount);
        for (int i = 0; i < persons->size; i++){
            if (isTeacher(persons->data[i])){
                printPerson(persons->data[i]);
            }
        }
    }
    
    printf("  Итого: %d человек\n", persons->size);
}

void printStudentsOnly(PersonArray* arr){
    printf("\n=== СТУДЕНТЫ ===\n");
    int count = 0;
    if (!arr || arr->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++){
        if (isStudent(arr->data[i])){
            printPerson(arr->data[i]);
            count++;
        }
    }
    if (count == 0) printf("  (нет студентов)\n");
    else printf("  Всего студентов: %d\n", count);
}

void printTeachersOnly(PersonArray* arr){
    printf("\n=== ПРЕПОДАВАТЕЛИ ===\n");
    int count = 0;
    if (!arr || arr->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++){
        if (isTeacher(arr->data[i])){
            printPerson(arr->data[i]);
            count++;
        }
    }
    if (count == 0) printf("  (нет преподавателей)\n");
    else printf("  Всего преподавателей: %d\n", count);
}