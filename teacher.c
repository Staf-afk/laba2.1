#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"

Teacher* createTeacher(char* firstName, char* secondName, char* lastName,
                       int dayBirth, int monthBirth, int yearBirth,
                       Person_ID* id, int salary){
    Teacher* t = (Teacher*)malloc(sizeof(Teacher));
    if (!t){
        printf("Ошибка выделения памяти.\n");
        return NULL;
    }
    
    t->base.firstName = strdup(firstName);
    t->base.secondName = strdup(secondName);
    t->base.lastName = strdup(lastName);
    t->base.dayBirth = dayBirth;
    t->base.monthBirth = monthBirth;
    t->base.yearBirth = yearBirth;
    t->base.id = *id;
    t->base.type = PERSON_TEACHER;
    t->salary = salary;
    
    return t;
}