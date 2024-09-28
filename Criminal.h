#ifndef _CRIMINAL_
#define _CRIMINAL_

#include "CriminalRecord.h"

typedef enum { eKnown, eCaught, eArrested, eNoOfStatus } StatusType;
static const char* status[eNoOfStatus] = { "Known","Caught","Arrested" };


typedef struct {
    CriminalRecord record;
    char* name;
    int health;
    StatusType type;
}Criminal;

void initCriminal(Criminal* criminal, struct PoliceManager* manager);
void printCriminal(const Criminal* criminal);
void freeCriminal(Criminal* criminal);
#endif