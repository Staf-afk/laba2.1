#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"

int teacherGetPayment(void* self) {
    if (!self) return 0;
    Teacher* t = (Teacher*)self;
    return t->salary;
}

Teacher* createTeacher(char* firstName, char* secondName, char* lastName,
    int dayBirth, int monthBirth, int yearBirth,
    Person_ID* id, int salary){
    
    Teacher* s = (Teacher*)malloc(sizeof(Teacher));
    if (!s) return NULL;

    s->base.firstName = firstName ? strdup(firstName) : strdup("");
    s->base.secondName = secondName ? strdup(secondName) : strdup("");
    s->base.lastName = lastName ? strdup(lastName) : strdup("");

    if (!s->base.firstName || !s->base.secondName || !s->base.lastName) {
        if (s->base.firstName) free(s->base.firstName);
        if (s->base.secondName) free(s->base.secondName);
        if (s->base.lastName) free(s->base.lastName);
        free(s);
        return NULL;
    }

    s->base.dayBirth = dayBirth;
    s->base.monthBirth = monthBirth;
    s->base.yearBirth = yearBirth;
    s->base.id = *id;
    s->base.type = PERSON_TEACHER;
    s->salary = salary;
    s->base.getPayment = teacherGetPayment;
    return s;
}