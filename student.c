#include <stdlib.h>
#include <string.h>
#include "student.h"

int studentGetPayment(void* self) {
    if (!self) return 0;
    Student* s = (Student*)self;
    return s->scholarship;
}

Student* createStudent(char* firstName, char* secondName, char* lastName,
    int dayBirth, int monthBirth, int yearBirth,
    Person_ID* id, int scholarship){
    
    Student* s = (Student*)malloc(sizeof(Student));
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
    s->base.type = PERSON_STUDENT;
    s->scholarship = scholarship;
    s->base.getPayment = studentGetPayment;
    return s;
}