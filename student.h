#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ‡„…‘œ Œƒ‹€ › ›’œ ‚€˜€ …Š‹€Œ€,           ||
||      ‹ˆ˜œ ‡€  „ €‹‹› ‡€ ‹€“               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/


Student* createStudent(char* firstName, 
                    char* secondName, 
                    char* lastName,
                    int dayBirth, 
                    int monthBirth, 
                    int yearBirth,
                    Person_ID* id, 
                    int scholarship);




#endif