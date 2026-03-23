#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"
#include "student.h"
#include "teacher.h"

int addPrefixToPersonName(PersonBase* p){
    if (!p || !p->firstName) return 0;
    char* newFirst = malloc(strlen(p->firstName) + 19);
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
    
    printf("  -- Студенты:\n");
    int studentCount = 0;
    for (int i = 0; i < persons->size; i++){
        if (isStudent(persons->data[i])){
            printf("%d", studentCount + 1);
            printPerson(persons->data[i]);
            studentCount++;
        }
    }
    if (studentCount == 0) printf("  (нет студентов)\n");
    
    printf("  -- Преподаватели:\n");
    int teacherCount = 0;
    for (int i = 0; i < persons->size; i++){
        if (isTeacher(persons->data[i])){
            printf("%d", studentCount + teacherCount + 1);
            printPerson(persons->data[i]);
            teacherCount++;
        }
    }
    if (teacherCount == 0) printf("  (нет преподавателей)\n");
    
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
    if (count == 0){
        printf("  (нет преподавателей)\n");
    }
    else{ 
        printf("  Всего преподавателей: %d\n", count);
    }
}

void isValidName(char* name){
    if (name == NULL || strlen(name) == 0){
        printf("Вы ничего не ввели.\n");
        return;
    }

    if (strlen(name) > 50){
        printf("Сомнительная длина имени.\n");
        return;
    }

    for (int i = 0; name[i] != '\0'; i++){
        if (isdigit((unsigned char)name[i])){
            printf("Вы ввели цифру в имени(что-то явно не так).\n");
            return;  
        }
    }
}

void isValidDate(int day, int month, int year){
    if(day >= 32 || day <= 0 || month <= 0 || month >= 13 || year >= 2010 || year <= 1920){}
}

/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ЗДЕСЬ МОГЛА БЫ БЫТЬ ВАША РЕКЛАМА,           ||
||      ЛИШЬ ЗА  ДОП БАЛЛЫ ЗА ЛАБУ               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/