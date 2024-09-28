#include <stdlib.h>

#include "SystemBin.h"
#include "FileHelperBin.h"

int saveSystem(const PoliceManager* manager, const char* systemBin) {
    FILE* file = fopen(systemBin, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        fclose(file);
        return 0;
    }

    // Save counts
    fwrite(&manager->criminalCounter, sizeof(int), 1, file);
    fwrite(&manager->vehicleCounter, sizeof(int), 1, file);
    fwrite(&manager->copsCounter, sizeof(int), 1, file);
    fwrite(&manager->cellCount, sizeof(int), 1, file);

    // Save criminals
    for (int i = 0; i < manager->criminalCounter; i++) {
        Criminal* criminal = &manager->criminals[i];
        saveCriminalRecord(file, &criminal->record);
        saveString(file, criminal->name);
        fwrite(&criminal->health, sizeof(int), 1, file);
        fwrite(&criminal->type, sizeof(StatusType), 1, file);
    }

    // Save vehicles from the linked list
    saveVehiclesCompressed(file, &manager->VehicleList, manager);

    // Save cops
    for (int i = 0; i < manager->copsCounter; i++) {
        Cop* cop = manager->cops[i];
        saveString(file, cop->name);
        fwrite(&cop->id, sizeof(int), 1, file);
        fwrite(&cop->health, sizeof(int), 1, file);
        fwrite(&cop->numOfCriminals, sizeof(int), 1, file);
        fwrite(&cop->proficiencyType, sizeof(int), 1, file);

        // Serialize each criminal associated with the cop
        for (int j = 0; j < cop->numOfCriminals; j++) {
            fwrite(cop->criminals[j].record.caseCode, CODE_LEN, 1, file);
        }

        // Serialize Cop's Vehicle
        fwrite(&cop->vehicle->number, sizeof(int), 1, file);
    }


    // Save prison cells
    savePrisonCells(file, manager->cells, MAX_CELLS);

    fclose(file);
    return 1;
}

int loadSystemState(PoliceManager* manager, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        fclose(file);
        return 0;
    }

    fread(&manager->criminalCounter, sizeof(int), 1, file);
    fread(&manager->vehicleCounter, sizeof(int), 1, file);
    fread(&manager->copsCounter, sizeof(int), 1, file);
    fread(&manager->cellCount, sizeof(int), 1, file);

    loadCriminals(file, manager);
    loadVehiclesCompressed(manager, file);

    // Assuming manager->cops and other arrays are initialized to NULL
    manager->cops = calloc(manager->copsCounter, sizeof(Cop*));
    for (int i = 0; i < manager->copsCounter; i++) {
        Cop* cop = calloc(1, sizeof(Cop));
        cop->name = loadString(file);
        fread(&cop->id, sizeof(int), 1, file);
        fread(&cop->health, sizeof(int), 1, file);
        fread(&cop->numOfCriminals, sizeof(int), 1, file);
        fread(&cop->proficiencyType, sizeof(ProficiencyType), 1, file);
        cop->criminals = calloc(cop->numOfCriminals, sizeof(Criminal));
        for (int j = 0; j < cop->numOfCriminals; j++) {
            char code[CODE_LEN + 1] = { 0 };
            fread(code, sizeof(char), CODE_LEN, file);
            Criminal* criminal = findCriminalByCode(manager, code, 0);
            if (criminal != NULL) {
                cop->criminals[j] = *criminal;
            }
        }

        int num;
        fread(&num, sizeof(int), 1, file);
        Vehicle* v = findVehicleByNum(num, manager);
        if (v != NULL) {
            cop->vehicle = v;
        }


        manager->cops[i] = cop;
    }


    for (int i = 0; i < manager->cellCount; i++) {
        loadPrisonCell(manager, file, &manager->cells[i]);
    }

    fclose(file);
    return 1;
}