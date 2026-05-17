#ifndef PERSON_H
#define PERSON_H
#include <inttypes.h>
#include <stddef.h>

typedef enum{
    ERROR_OK = 0,
    ERROR_MEMORY_ALLOCATION = -1,
    ERROR_NULL_POINTER = -2,
    ERROR_INVALID_INDEX = -3,
    ERROR_EMPTY_LIST = -4,
    ERROR_INVALID_NAME = -5,
    ERROR_INVALID_DATE = -6,
    ERROR_NOT_FOUND = -7,
    ERROR_MAPPER_FAILED = -8
} CodeError;

const char* errorInWords(CodeError error);

typedef enum{
    FORMAT_STRUCTURE,
    FORMAT_SINGLE_NUMBER,
    FORMAT_SPACE_SEPARATED
} PassportFormat;

typedef enum {
    CURRENCY_RUB,
    CURRENCY_USD
} CurrencyType;

typedef struct{
    unsigned int series;
    unsigned int number;
} Person_ID;

typedef struct PersonBase PersonBase;

typedef struct PersonBase{
    char* firstName;
    char* secondName;
    char* lastName;
    uint8_t dayBirth;
    uint8_t monthBirth;
    uint16_t yearBirth;
    Person_ID id;
    CurrencyType currency;

    void* (*getPayment)(PersonBase* self);
    void (*destroy)(PersonBase* self);
    int (*comparePassport)(PersonBase* self, Person_ID* id, PassportFormat format);
    char* (*getFullName)(PersonBase* self);
    char* (*toString)(PersonBase* self);
} PersonBase;

typedef struct {
    PersonBase base;
    unsigned int scholarship;
} Student;

typedef struct {
    PersonBase base;
    unsigned int salary;
} Teacher;

typedef struct{
    PersonBase* data;
    size_t size;
    PassportFormat passportFormat;
} PersonArray;

CodeError initPersonList(PersonArray* arr, PassportFormat format);
CodeError addPerson(PersonArray* arr, PersonBase* person);
CodeError removePerson(PersonArray* arr, size_t index);
void freePersonArray(PersonArray* arr);
PersonBase* findPersonByID(PersonArray* arr, unsigned int series, unsigned int number);

const char* currencyToString(CurrencyType currency);
int comparePassportIDs(Person_ID* id1, Person_ID* id2, PassportFormat format);

#endif