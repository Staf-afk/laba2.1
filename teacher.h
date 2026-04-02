#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"

Teacher* createTeacher(char* firstName, 
                        char* secondName, 
                        char* lastName,
                       int dayBirth, 
                       int monthBirth, 
                       int yearBirth,
                       Person_ID* id, 
                       int salary);

#endif