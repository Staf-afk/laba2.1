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

char* errorInWords(CodeError error);

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


typedef enum {
    PERSON_STUDENT = 1,
    PERSON_TEACHER = 2
} PersonType;

typedef enum {
    PAYMENT_TYPE_INT,
    PAYMENT_TYPE_DOUBLE
} PaymentType;


typedef struct PersonBase{
    char* firstName;
    char* secondName;
    char* lastName;
    uint8_t dayBirth;
    uint8_t monthBirth;
    uint16_t yearBirth;
    Person_ID id;
    PersonType type;
    CurrencyType currency;
    void* (*getPayment)(struct PersonBase* self);
} PersonBase;

/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ‡„…‘œ Œƒ‹€ › ›’œ ‚€˜€ …Š‹€Œ€,           ||
||           ‡€  „ €‹‹› ‡€ ‹€“               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/

typedef struct {
    PersonBase base;
    unsigned int scholarship;
} Student;


typedef struct {
    PersonBase base;
    unsigned int salary;
} Teacher;

/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ‡„…‘œ Œƒ‹€ › ›’œ ‚€˜€ …Š‹€Œ€,           ||
||           ‡€  „ €‹‹› ‡€ ‹€“               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/

typedef struct{
    PersonBase* data;
    size_t size;
} PersonArray;


extern PassportFormat g_passportFormat;


void setPassportFormat(PassportFormat format);

PassportFormat getPassportFormat(void);

int comparePassportIDs(Person_ID* id1, Person_ID* id2);

void printPassportID(Person_ID* id);




CodeError  initPersonList(PersonArray* arr);

CodeError  addPerson(PersonArray* arr, PersonBase* person);

CodeError removePerson(PersonArray* arr, size_t index);

void freePersonArray(PersonArray* arr);

void printPerson(PersonBase* p);

void printAllPersons(PersonArray* arr);



PersonBase* findPersonByID(PersonArray* arr, unsigned int series, unsigned int number);

Student* findStudentByIndex(PersonArray* arr, size_t index);

Teacher* findTeacherByIndex(PersonArray* arr, size_t index);



int isStudent(PersonBase* p);

int isTeacher(PersonBase* p);

char* currencyToString(CurrencyType currency);


#endif