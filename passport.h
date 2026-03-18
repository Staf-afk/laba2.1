#ifndef PASSPORT_H
#define PASSPORT_H

typedef enum{
    FORMAT_STRUCTURE = 1,
    FORMAT_SPACE_SEPARATED = 2,
    FORMAT_SINGLE_NUMBER = 3
} PassportFormat;

typedef struct{
    int series;
    int number;
} Person_ID;

typedef Person_ID Student_ID;
typedef Person_ID Teacher_ID;

extern PassportFormat g_passportFormat;

void setPassportFormat(PassportFormat format);
PassportFormat getPassportFormat(void);
int comparePassportIDs(Person_ID* id1, Person_ID* id2);
void printPassportID(Person_ID* id);

#endif