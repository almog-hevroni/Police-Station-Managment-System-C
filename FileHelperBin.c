#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileHelperBin.h"
#include "Macros.h"

void saveString(FILE* file, const char* str) {
    if (str == NULL) {
        int length = 0;
        fwrite(&length, sizeof(length), 1, file);
    }
    else {
        int length = (int)strlen(str) + 1; // Including null terminator
        fwrite(&length, sizeof(length), 1, file);
        fwrite(str, sizeof(char), length, file);
    }
}

void saveCriminalRecord(FILE* file,const CriminalRecord* record) {
    fwrite(record->caseCode, CODE_LEN, 1, file);
    saveDate(file, &record->date);
    saveEvidence(file, &record->evidence);
}

void saveEvidence(FILE* file, const Evidence* theEvidence) {
    fwrite(&theEvidence->evidenceType, sizeof(evidenceType), 1, file);
    saveString(file, theEvidence->description);
}

void saveDate(FILE* file,const Date* date) {
    fwrite(date, sizeof(Date), 1, file);
}

void saveVehiclesCompressed(FILE* file, const LIST* vehicleList, const PoliceManager* manager) {
    NODE* currentNode = vehicleList->head.next;
    for (int i = 0; i < manager->vehicleCounter; i++) {
        Vehicle* theVehicle = (Vehicle*)currentNode->key;
        // Prepare data with masks and shifting
        unsigned int data = ((theVehicle->number & 0x3FFFFFFF) << 2) | (theVehicle->type & 0x3);
        fwrite(&data, sizeof(data), 1, file);
        currentNode = currentNode->next;
    }
    // Mark the end of the list
    unsigned int endOfListMarker = 0xFFFFFFFF; // All bits set
    fwrite(&endOfListMarker, sizeof(endOfListMarker), 1, file);
}

void savePrisonCells(FILE* file, const PrisonCell* cells,const int cellCount) {
    for (int i = 0; i < cellCount; i++) {
        fwrite(&cells[i].serialNumber, sizeof(int), 1, file);
        fwrite(&cells[i].numOfCriminals, sizeof(int), 1, file);
        fwrite(&cells[i].occupied, sizeof(int), 1, file);
        for (int j = 0; j < cells[i].numOfCriminals; j++) {
            if (cells[i].numOfCriminals > 0) {
                for (int k = 0; k < cells[i].numOfCriminals; k++) {
                    fwrite(cells[i].criminals[j].record.caseCode, CODE_LEN, 1, file);
                }
            }
        }
    }
}

char* loadString(FILE* file) {
    int length;
    fread(&length, sizeof(length), 1, file);
    if (length == 0) return NULL;
    char* str = calloc(length, sizeof(char));
    fread(str, sizeof(char), length, file);
    return str;
}

Criminal* loadCriminal(FILE* file) {
    Criminal* criminal = calloc(1, sizeof(Criminal));
    loadCriminalRecord(file, &criminal->record);
    criminal->name = loadString(file);
    fread(&criminal->health, sizeof(criminal->health), 1, file);
    fread(&criminal->type, sizeof(criminal->type), 1, file);
    return criminal;
}

void loadCriminals(FILE* file, PoliceManager* manager) {
    manager->criminals = calloc(manager->criminalCounter, sizeof(Criminal));
    for (int i = 0; i < manager->criminalCounter; i++) {
        Criminal* criminal = loadCriminal(file);
        manager->criminals[i] = *criminal; 
        free(criminal);
    }
}

void loadVehiclesCompressed(PoliceManager* manager, FILE* file) {
    unsigned int data;
    while (fread(&data, sizeof(data), 1, file) == 1) { // Ensure we successfully read one item
        if (data == 0xFFFFFFFF) { // Check for end-of-list marker
            break; // End the loop if the marker is found
        }

        Vehicle* theVehicle = calloc(1, sizeof(Vehicle));
        theVehicle->number = (data >> 2) & 0x3FFFFFFF; // Extract 30 bits for the number
        theVehicle->type = data & 0x3; // Extract 2 bits for the type
        NODE* newNode = ALLOCATE(NODE, 1);
        newNode->key = theVehicle;
        manager->VehicleList.head.next = L_insert((NODE*)&manager->VehicleList.head, newNode->key);
    }
}

void loadPrisonCell(PoliceManager* manager, FILE* file, PrisonCell* cell) {
    fread(&cell->serialNumber, sizeof(int), 1, file);
    fread(&cell->numOfCriminals, sizeof(int), 1, file);
    fread(&cell->occupied, sizeof(int), 1, file);
    for (int i = 0; i < cell->numOfCriminals; i++) {
        char code[CODE_LEN + 1] = { 0 };
        fread(&code, CODE_LEN, 1, file);
        Criminal* criminal = findCriminalByCode(manager, (const char*)code, 0);
        if (criminal != NULL)
            cell->criminals[i] = *(Criminal*)criminal;
    }
}

void loadCriminalRecord(FILE* file, CriminalRecord* record) {
    fread(record->caseCode, CODE_LEN, 1, file);
    loadDate(file, &record->date);
    loadEvidence(file, &record->evidence);
}

void loadEvidence(FILE* file, Evidence* theEvidence) {
    fread(&theEvidence->evidenceType, sizeof(evidenceType), 1, file);
    theEvidence->description = loadString(file);
}

void loadDate(FILE* file, Date* date) {
    fread(date, sizeof(Date), 1, file);
}