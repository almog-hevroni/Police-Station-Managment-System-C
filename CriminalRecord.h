#ifndef _CRIMINALRECORD_
#define _CRIMINALRECORD_

#include "Date.h"
#include "Evidence.h"

#define CODE_LEN 4

struct PoliceManager;

typedef struct {
    char caseCode[CODE_LEN + 1];
    Date date;
    Evidence evidence;
}CriminalRecord;

void initRecord(CriminalRecord* record, struct PoliceManager* manager);
void getCaseCode(char* code);
void printRecord(const CriminalRecord* criminalRecord);

#endif