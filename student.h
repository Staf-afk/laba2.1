#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

Student* createStudent(char* firstName, 
                    char* secondName, 
                    char* lastName,
                    uint8_t dayBirth, 
                    uint8_t monthBirth, 
                    uint16_t yearBirth,
                    Person_ID* id, 
                    unsigned int scholarship,
                    CurrencyType currency);

#endif