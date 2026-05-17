#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "teacher.h"

void* teacherGetPayment(PersonBase* self){
    if (!self) return NULL;
    Teacher* t = (Teacher*)self;
    return (void*)&t->salary;
}

void teacherDestroy(PersonBase* self){
    if(!self) return;
    if(self->firstName) free(self->firstName);
    if(self->secondName) free(self->secondName);
    if(self->lastName) free(self->lastName);
}

int teacherComparePassport(PersonBase* self, Person_ID* id, PassportFormat format){
    if(!self || !id) return 0;
    return comparePassportIDs(&self->id, id, format);
}

char* teacherGetFullName(PersonBase* self){
    if(!self) return NULL;
    size_t len = strlen(self->lastName) + strlen(self->firstName) + 
                 strlen(self->secondName) + 3;
    char* fullName = malloc(len);
    if(fullName){
        snprintf(fullName, len, "%s %s %s", self->lastName, self->firstName, self->secondName);
    }
    return fullName;
}

char* teacherToString(PersonBase* self){
    if(!self) return NULL;
    Teacher* t = (Teacher*)self;
    
    size_t size = snprintf(NULL, 0, "[Преподаватель] %s %s %s | ЗП: %u %s | Дата рождения: %hhu.%hhu.%hu",
                          t->base.lastName, t->base.firstName, t->base.secondName,
                          t->salary, currencyToString(t->base.currency),
                          t->base.dayBirth, t->base.monthBirth, t->base.yearBirth) + 1;
    
    char* result = malloc(size);
    if(result){
        snprintf(result, size, "[Преподаватель] %s %s %s | ЗП: %u %s | Дата рождения: %hhu.%hhu.%hu",
                t->base.lastName, t->base.firstName, t->base.secondName,
                t->salary, currencyToString(t->base.currency),
                t->base.dayBirth, t->base.monthBirth, t->base.yearBirth);
    }
    return result;
}

Teacher* createTeacher(char* firstName,
    char* secondName, 
    char* lastName,
    uint8_t dayBirth, 
    uint8_t monthBirth, 
    uint16_t yearBirth,
    Person_ID* id, 
    unsigned int salary, 
    CurrencyType currency){
    
    Teacher* t = (Teacher*)malloc(sizeof(Teacher));
    if (!t) return NULL;
    t->base.firstName = firstName ? strdup(firstName) : strdup("");
    t->base.secondName = secondName ? strdup(secondName) : strdup("");
    t->base.lastName = lastName ? strdup(lastName) : strdup("");
    if (!t->base.firstName || !t->base.secondName || !t->base.lastName) {
        if (t->base.firstName) free(t->base.firstName);
        if (t->base.secondName) free(t->base.secondName);
        if (t->base.lastName) free(t->base.lastName);
        free(t);
        return NULL;
    }

    t->base.dayBirth = dayBirth;
    t->base.monthBirth = monthBirth;
    t->base.yearBirth = yearBirth;
    t->base.id = *id;
    t->base.currency = currency;
    t->salary = salary;
    t->base.getPayment = teacherGetPayment;
    t->base.destroy = teacherDestroy;
    t->base.comparePassport = teacherComparePassport;
    t->base.getFullName = teacherGetFullName;
    t->base.toString = teacherToString;
    
    return t;
}