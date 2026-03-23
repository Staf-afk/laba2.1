#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

PassportFormat g_passportFormat = FORMAT_STRUCTURE;

void setPassportFormat(PassportFormat format){
    g_passportFormat = format;
}

PassportFormat getPassportFormat(void){
    return g_passportFormat;
}

int comparePassportIDs(Person_ID* id1, Person_ID* id2){
    if(!id1 || !id2) return 0;
    if(g_passportFormat == FORMAT_SINGLE_NUMBER){
        return (id1->series == id2->series);
    }
    else{
        return (id1->series == id2->series && id1->number == id2->number);
    }
}

void printPassportID(Person_ID* id){
    if(!id) return;
    if(g_passportFormat == FORMAT_SINGLE_NUMBER){
        printf("ID: %d", id->series);
    }
    else if(g_passportFormat == FORMAT_SPACE_SEPARATED){
        printf("Паспорт: %d %d", id->series, id->number);
    }
    else{
        printf("Паспорт: %d %d", id->series, id->number);
    }
}

void initPersonList(PersonArray* arr){
    arr->data = NULL;
    arr->size = 0;
}

void addPerson(PersonArray* arr, PersonBase* person){
    PersonBase** newData = (PersonBase**)realloc(arr->data, (arr->size + 1) * sizeof(PersonBase*));
    if (newData == NULL){
        printf("Ошибка выделения памяти.\n");
        return;
    }
    arr->data = newData;
    arr->data[arr->size] = person;
    arr->size++;
}

void removePerson(PersonArray* arr, int index){
    if (index < 0 || index >= arr->size){
        printf("Неверный индекс человека.\n");
        return;
    }
    
    PersonBase* p = arr->data[index];
    free(p->firstName);
    free(p->secondName);
    free(p->lastName);
    free(p);
    
    if (arr->size == 1){
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        printf("Последний человек удален. Массив пуст.\n");
        return;
    }
    
    if (arr->size == 1){
        free(arr->data);
        arr->data = NULL;
    } 
    else{
        for (int i = index; i < arr->size - 1; i++){
            arr->data[i] = arr->data[i + 1];
        }
        PersonBase** newData = (PersonBase**)realloc(arr->data, (arr->size - 1) * sizeof(PersonBase*));
        if (newData) arr->data = newData;
    }
    arr->size--;
    printf("Человек с индексом %d удален. Осталось: %d\n", index + 1, arr->size);
}

void freePersonArray(PersonArray* arr){
    if (arr->data != NULL){
        for (int i = 0; i < arr->size; i++){
            PersonBase* p = arr->data[i];
            free(p->firstName);
            free(p->secondName);
            free(p->lastName);
            free(p);
        }
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = 0;
}

int isStudent(PersonBase* p){
    return p && p->type == PERSON_STUDENT;
}

int isTeacher(PersonBase* p){
    return p && p->type == PERSON_TEACHER;
}

void printPerson(PersonBase* p){
    if (!p) return;
    
    if (isStudent(p)){
        Student* s = (Student*)p;
        printf("  [Студент] %s %s %s | Стипендия: %d | Дата рождения: %d.%d.%d\n",
               p->lastName, p->firstName, p->secondName,
               s->scholarship, p->dayBirth, p->monthBirth, p->yearBirth);
    }
    else if (isTeacher(p)){
        Teacher* t = (Teacher*)p;
        printf("  [Преподаватель] %s %s %s | ЗП: %d | Дата рождения: %d.%d.%d\n",
               p->lastName, p->firstName, p->secondName,
               t->salary, p->dayBirth, p->monthBirth, p->yearBirth);
    }
}

void printAllPersons(PersonArray* arr){
    if (!arr || arr->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++){
        printPerson(arr->data[i]);
    }
}

PersonBase* findPersonByID(PersonArray* arr, int series, int number){
    if (!arr || arr->data == NULL) return NULL;
    Person_ID searchID = {series, number};
    
    for (int i = 0; i < arr->size; i++){
        if (comparePassportIDs(&arr->data[i]->id, &searchID)){
            return arr->data[i];
        }
    }
    return NULL;
}

Student* findStudentByIndex(PersonArray* arr, int index){
    if (!arr || index < 0 || index >= arr->size) return NULL;
    PersonBase* p = arr->data[index];
    return isStudent(p) ? (Student*)p : NULL;
}

Teacher* findTeacherByIndex(PersonArray* arr, int index){
    if (!arr || index < 0 || index >= arr->size) return NULL;
    PersonBase* p = arr->data[index];
    return isTeacher(p) ? (Teacher*)p : NULL;
}