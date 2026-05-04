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
                    uint8_t dayBirth, 
                    uint8_t monthBirth, 
                    uint8_t yearBirth,
                    Person_ID* id, 
                    int scholarship);




#endif