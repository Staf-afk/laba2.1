#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

Student* createStudent(char* firstName, char* secondName, char* lastName,
                       int dayBirth, int monthBirth, int yearBirth,
                       Person_ID* id, int scholarship);

#endif