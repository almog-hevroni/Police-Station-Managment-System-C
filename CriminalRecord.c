#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "CriminalRecord.h"
#include "GeneralFunc.h"
#include "PoliceManager.h"

void initRecord(CriminalRecord* record, struct PoliceManager* manager)
{
    getCaseCode(record->caseCode);
    do
    {
        if (findCriminalByCode((PoliceManager*)manager, record->caseCode, 0) != NULL)
        {
            printf("Case code already exists\n");
            getCaseCode(record->caseCode);
        }
        else
            break;
    } while (1);
    getCorrectDate(&record->date);
    initEvidence(&record->evidence);
}

void getCaseCode(char* code)
{
    char temp[MAX_STR_LEN];
    int ok = 1;
    do {
        ok = 1;
        printf("Enter cade code  - %d UPPER CASE letters\t", CODE_LEN);
        myGets(temp, MAX_STR_LEN);
        if (strlen(temp) != CODE_LEN)
        {
            printf("code should be %d letters\n", CODE_LEN);
            ok = 0;
        }
        else {
            for (int i = 0; i < CODE_LEN; i++)
            {
                if (isupper(temp[i]) == 0 && isdigit(temp[i]) == 0)
                {
                    printf("Code should be upper case letters and digits only\n");
                    ok = 0;
                    break;
                }
            }
        }
    } while (!ok);

    strcpy(code, temp);
}


void printRecord(const CriminalRecord* criminalRecord) {
    printf("Case Code: %s\n", criminalRecord->caseCode);
    printf("Date: ");
    printDate(&criminalRecord->date);
    printf("Evidence Details:\n");
    printEvidence(&criminalRecord->evidence);
}