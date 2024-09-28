#include <stdio.h>
#include <stdlib.h>

#include "Criminal.h"
#include "GeneralFunc.h"
#include "Macros.h"


void initCriminal(Criminal* criminal, struct PoliceManager* manager) {
    initRecord(&criminal->record, manager);
    criminal->name = getStr("Please enter the name of the Criminal: ", 1);
    criminal->health = 100;
    criminal->type = (StatusType)0;
}

void printCriminal(const Criminal* criminal) {
    printf("Name: %s\nHealth: %d, Status: %s\nCriminal Record:\n", criminal->name, criminal->health, status[criminal->type]);
    printRecord(&criminal->record);
    puts("");
}

void freeCriminal(Criminal* criminal) {
    SAFE_FREE(criminal->name);
    SAFE_FREE(criminal->record.evidence.description);
}
