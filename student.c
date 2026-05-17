#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "student.h"

void* studentGetPayment(PersonBase* self){
    if (!self) return NULL;
    Student* s = (Student*)self;
    return (void*)&s->scholarship;
}

void studentDestroy(PersonBase* self){
    if(!self) return;
    if(self->firstName) free(self->firstName);
    if(self->secondName) free(self->secondName);
    if(self->lastName) free(self->lastName);
}

int studentComparePassport(PersonBase* self, Person_ID* id){
    if(!self || !id) return 0;
    return comparePassportIDs(&self->id, id);
}

char* studentGetFullName(PersonBase* self){
    if(!self) return NULL;
    char* fullName = malloc(strlen(self->lastName) + strlen(self->firstName) + 
                           strlen(self->secondName) + 3);
    if(fullName){
        sprintf(fullName, "%s %s %s", self->lastName, self->firstName, self->secondName);
    }
    return fullName;
}

char* studentToString(PersonBase* self){
    if(!self) return NULL;
    Student* s = (Student*)self;

    size_t size = snprintf(NULL, 0, "[Студент] %s %s %s | Стипендия: %u %s | Дата рождения: %hhu.%hhu.%hu",
                          s->base.lastName, s->base.firstName, s->base.secondName,
                          s->scholarship, currencyToString(s->base.currency),
                          s->base.dayBirth, s->base.monthBirth, s->base.yearBirth) + 1;
    
    char* result = malloc(size);
    if(result){
        sprintf(result, "[Студент] %s %s %s | Стипендия: %u %s | Дата рождения: %hhu.%hhu.%hu",
                s->base.lastName, s->base.firstName, s->base.secondName,
                s->scholarship, currencyToString(s->base.currency),
                s->base.dayBirth, s->base.monthBirth, s->base.yearBirth);
    }
    return result;
}

Student* createStudent(char* firstName, 
    char* secondName, 
    char* lastName,
    uint8_t dayBirth, 
    uint8_t monthBirth, 
    uint16_t yearBirth,
    Person_ID* id, 
    unsigned int scholarship, 
    CurrencyType currency){
    
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
    s->base.currency = currency;
    s->scholarship = scholarship;
    s->base.getPayment = studentGetPayment;
    s->base.destroy = studentDestroy;
    s->base.comparePassport = studentComparePassport;
    s->base.getFullName = studentGetFullName;
    s->base.toString = studentToString;
    
    return s;
}