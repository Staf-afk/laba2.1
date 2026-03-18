#include <stdio.h>
#include "passport.h"

// …„ˆ‘’‚…… ®¯à¥¤¥«¥­¨¥ ¯¥à¥¬¥­­®©
PassportFormat g_passportFormat = FORMAT_STRUCTURE;

void setPassportFormat(PassportFormat format) {
    g_passportFormat = format;
}

PassportFormat getPassportFormat(void) {
    return g_passportFormat;
}

int comparePassportIDs(Person_ID* id1, Person_ID* id2) {
    if (!id1 || !id2) return 0;
    
    if (g_passportFormat == FORMAT_SINGLE_NUMBER) {
        return (id1->series == id2->series);
    } else {
        return (id1->series == id2->series && id1->number == id2->number);
    }
}

void printPassportID(Person_ID* id) {
    if (!id) return;
    
    if (g_passportFormat == FORMAT_SINGLE_NUMBER) {
        printf("ID: %d", id->series);
    } else {
        printf(" á¯®àâ: %d %d", id->series, id->number);
    }
}