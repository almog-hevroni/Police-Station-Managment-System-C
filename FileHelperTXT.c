#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileHelperTXT.h"
#include "Macros.h"

void saveStringTXT(FILE* file, const char* str) {
    if (str == NULL) {
        int length = 0;
        fprintf(file, "%d\n", length);
    }
    else {
        int length = (int)strlen(str) + 1; 
        fprintf(file, "%d\n", length);
        fprintf(file, "%s\n", str);
    }
}

void saveCriminalRecordTXT(FILE* file, const CriminalRecord* record) {
    fprintf(file, "%s\n", record->caseCode);
    saveDateTXT(file, &record->date);
    saveEvidenceTXT(file, &record->evidence);
}

void saveDateTXT(FILE* file, const Date* date) {
    fprintf(file, "%d %d %d\n", date->day, date->month, date->year);
}

void saveEvidenceTXT(FILE* file, const Evidence* theEvidence) {
    fprintf(file, "%d\n", theEvidence->evidenceType);
    saveStringTXT(file, theEvidence->description);
}


void saveVehiclesTXT(FILE* file, const LIST* vehicleList, const PoliceManager* manager) {
    NODE* currentNode = vehicleList->head.next;
    for (int i = 0; i < manager->vehicleCounter; i++) {
        Vehicle* theVehicle = (Vehicle*)currentNode->key;
        fprintf(file, "%d\n", theVehicle->number);
        fprintf(file, "%d\n", theVehicle->type);
        currentNode = currentNode->next;
    }

}

void savePrisonCellsTXT(FILE* file, const PrisonCell* cells, const int cellCount) {
    for (int i = 0; i < cellCount; i++) {
        fprintf(file, "%d\n", cells[i].serialNumber);
        fprintf(file, "%d\n", cells[i].numOfCriminals);
        fprintf(file, "%d\n", cells[i].occupied);
        for (int j = 0; j < cells[i].numOfCriminals; j++) {
            if (cells[i].numOfCriminals > 0) {
                for (int k = 0; k < cells[i].numOfCriminals; k++) {
                    fprintf(file, "%s\n", cells[i].criminals[j].record.caseCode);
                }
            }
        }
    }
}

char* loadStringTXT(FILE* file) {
    int length;
    fscanf(file, "%d\n", &length);
    if (length == 0) return NULL;
    char* str = calloc(length, sizeof(char));
    fscanf(file, " %[^\n]", str);
    return str;
}

Criminal* loadCriminalTXT(FILE* file) {
    Criminal* criminal = calloc(1, sizeof(Criminal));
    loadCriminalRecordTXT(file, &criminal->record);
    criminal->name = loadStringTXT(file);
    fscanf(file, "%d\n", &criminal->health);
    fscanf(file, "%d\n", &criminal->type);
    return criminal;
}

void loadCriminalsTXT(FILE* file, PoliceManager* manager) {
    manager->criminals = calloc(manager->criminalCounter, sizeof(Criminal));
    for (int i = 0; i < manager->criminalCounter; i++) {
        Criminal* criminal = loadCriminalTXT(file);
        manager->criminals[i] = *criminal; // Assuming shallow copy is sufficient; adjust as needed
        free(criminal);
    }
}

void loadVehiclesTXT(PoliceManager* manager, FILE* file) {
    //    int number;
    for (int i = 0; i < manager->vehicleCounter; i++) {
        Vehicle* theVehicle = calloc(1, sizeof(Vehicle));
        fscanf(file, "%d\n", &theVehicle->number);
        fscanf(file, "%d\n", &theVehicle->type);
        NODE* newNode = ALLOCATE(NODE, 1);
        newNode->key = theVehicle;
        manager->VehicleList.head.next = L_insert((NODE*)&manager->VehicleList.head, newNode->key);
    }
}

void loadPrisonCellTXT(PoliceManager* manager, FILE* file, PrisonCell* cell) {
    fscanf(file, "%d\n", &cell->serialNumber);
    fscanf(file, "%d\n", &cell->numOfCriminals);
    fscanf(file, "%d\n", &cell->occupied);
    for (int i = 0; i < cell->numOfCriminals; i++) {
        char code[CODE_LEN + 1] = { 0 };
        fscanf(file, "%s\n", code);
        Criminal* criminal = findCriminalByCode(manager, code, 0);
        if (criminal != NULL)
            cell->criminals[i] = *(Criminal*)criminal;
    }
}

void loadCriminalRecordTXT(FILE* file, CriminalRecord* record) {
    fscanf(file, "%s\n", record->caseCode);
    loadDateTXT(file, &record->date);
    loadEvidenceTXT(file, &record->evidence);
}

void loadEvidenceTXT(FILE* file, Evidence* theEvidence) {
    fscanf(file, "%d\n", &theEvidence->evidenceType);
    theEvidence->description = loadStringTXT(file);
}

void loadDateTXT(FILE* file, Date* date) {
    fscanf(file, "%d %d %d\n", &date->day, &date->month, &date->year);
}   