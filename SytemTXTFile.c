#include <stdlib.h>

#include "SystemBin.h"
#include "FileHelperBin.h"
#include "FileHelperTXT.h"

int saveSystemTXT(const PoliceManager* manager, const char* systemBin) {
    FILE* file = fopen(systemBin, "w");
    if (!file) {
        perror("Failed to open file for writing");
        fclose(file);
        return 0;
    }

    // Save counts
    fprintf(file, "%d\n", manager->criminalCounter);
    fprintf(file, "%d\n", manager->vehicleCounter);
    fprintf(file, "%d\n", manager->copsCounter);
    fprintf(file, "%d\n", manager->cellCount);

    // Save criminals
    for (int i = 0; i < manager->criminalCounter; i++) {
        Criminal* criminal = &manager->criminals[i];
        saveCriminalRecordTXT(file, &criminal->record);
        saveStringTXT(file, criminal->name);
        fprintf(file, "%d\n", criminal->health);
        fprintf(file, "%d\n", criminal->type);
    }

    // Save vehicles from the linked list
    saveVehiclesTXT(file, &manager->VehicleList, manager);

    // Save cops
    for (int i = 0; i < manager->copsCounter; i++) {
        Cop* cop = manager->cops[i];
        saveStringTXT(file, cop->name);
        fprintf(file, "%d\n", cop->id);
        fprintf(file, "%d\n", cop->health);
        fprintf(file, "%d\n", cop->numOfCriminals);
        fprintf(file, "%d\n", cop->proficiencyType);

        // Serialize each criminal associated with the cop
        for (int j = 0; j < cop->numOfCriminals; j++) {
            fprintf(file, "%s\n", cop->criminals[j].record.caseCode);
        }

        // Serialize Cop's Vehicle
        fprintf(file, "%d\n", cop->vehicle->number);
    }

    // Save prison cells
    savePrisonCellsTXT(file, manager->cells, MAX_CELLS);

    fclose(file);
    return 1;
}

int loadSystemStateToTXT(PoliceManager* manager, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for reading");
        fclose(file);
        return 0;
    }

    fscanf(file, "%d\n", &manager->criminalCounter);
    fscanf(file, "%d\n", &manager->vehicleCounter);
    fscanf(file, "%d\n", &manager->copsCounter);
    fscanf(file, "%d\n", &manager->cellCount);

    loadCriminalsTXT(file, manager);
    loadVehiclesTXT(manager, file);

    // Assuming manager->cops and other arrays are initialized to NULL
    manager->cops = calloc(manager->copsCounter, sizeof(Cop*));
    for (int i = 0; i < manager->copsCounter; i++) {
        Cop* cop = calloc(1, sizeof(Cop));
        cop->name = loadStringTXT(file);
        fscanf(file, "%d\n", &cop->id);
        fscanf(file, "%d\n", &cop->health);
        fscanf(file, "%d\n", &cop->numOfCriminals);
        fscanf(file, "%d\n", &cop->proficiencyType);
        cop->criminals = calloc(cop->numOfCriminals, sizeof(Criminal));
        for (int j = 0; j < cop->numOfCriminals; j++) {
            char code[CODE_LEN + 1] = { 0 };
            fscanf(file, "%s\n", code);
            Criminal* criminal = findCriminalByCode(manager, code, 0);
            if (criminal != NULL) {
                cop->criminals[j] = *criminal;
            }
        }

        int num;
        fscanf(file, "%d\n", &num);
        Vehicle* v = findVehicleByNum(num, manager);
        if (v != NULL) {
            cop->vehicle = v;
        }


        manager->cops[i] = cop;
    }


    for (int i = 0; i < manager->cellCount; i++) {
        loadPrisonCellTXT(manager, file, &manager->cells[i]);
    }

    fclose(file);
    return 1;
}