#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

Student* createStudent(char* firstName, char* secondName, char* lastName,
                       int dayBirth, int monthBirth, int yearBirth,
                       Person_ID* id, int scholarship){
    Student* s = (Student*)malloc(sizeof(Student));
    if (!s){
        printf("Ошибка выделения памяти.\n");
        return NULL;
    }
    
    s->base.firstName = strdup(firstName);
    s->base.secondName = strdup(secondName);
    s->base.lastName = strdup(lastName);
    if (!s->base.firstName || !s->base.secondName || !s->base.lastName){
        printf("Ошибка выделения памяти для строк.\n");
        free(s);
        return NULL;
    }
    s->base.dayBirth = dayBirth;
    s->base.monthBirth = monthBirth;
    s->base.yearBirth = yearBirth;
    s->base.id = *id;
    s->base.type = PERSON_STUDENT;
    s->scholarship = scholarship;
    
    return s;
}