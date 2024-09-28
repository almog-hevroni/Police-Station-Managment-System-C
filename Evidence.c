#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Evidence.h"
#include "GeneralFunc.h"

void initEvidence(Evidence* theEvidence) {
    theEvidence->evidenceType = getEvidenceType();
    theEvidence->description = getEvidenceDescription();
}

evidenceType getEvidenceType() {
    do {
        puts("What type of evidence do you have?");
        int type;
        for (int i = 0; i < eNoOfEvidence; i++) {
            printf("%d) %s\n", i, evidence[i]);
        }
        scanf("%d", &type);

        if (type < 0 || type > 2)
            puts("Error! try again.");
        else return (evidenceType)type;
    } while (1);
}

char* getEvidenceDescription() {
    char* temp;
    do {
        temp = getStr("Please enter a description of the the Evidence:", 0);
        if (strlen(temp) < 10) {
            puts("Description should be at least 10 characters long.");
        }
        else return temp;
    } while (1);
}

void printEvidence(const Evidence* theEvidence) {
    printf("Evidence type: %s\nDescription: %s\n", evidence[theEvidence->evidenceType], theEvidence->description);
}