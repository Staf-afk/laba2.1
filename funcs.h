#ifndef FUNCS_H
#define FUNCS_H

#include "person.h"

int addPrefixToPersonName(PersonBase* p);
PersonArray* mapPersons(PersonArray* arr, int (*mapper)(PersonBase*));
void concatPrint(PersonArray* persons);
void printStudentsOnly(PersonArray* arr);
void printTeachersOnly(PersonArray* arr);

#endif