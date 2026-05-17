#ifndef FUNCS_H
#define FUNCS_H

#include "person.h"

int addPrefixToPersonName(PersonBase* p);
PersonArray* mapPersons(PersonArray* arr, int (*mapper)(PersonBase*));
CodeError isValidName(char* name);
CodeError isValidDate(uint8_t day, uint8_t month, uint16_t year);
char* getPaymentString(PersonBase* p);



#endif