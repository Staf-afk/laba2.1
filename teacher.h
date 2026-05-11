#ifndef TEACHER_H
#define TEACHER_H

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


Teacher* createTeacher(char* firstName, 
                       char* secondName, 
                       char* lastName,
                       uint8_t dayBirth, 
                       uint8_t monthBirth, 
                       uint16_t yearBirth,
                       Person_ID* id, 
                       unsigned int salary,
                       CurrencyType currency);

#endif