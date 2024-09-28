#include <stdio.h>

#include "PrisonCell.h"
#include "PoliceManager.h"
#include "GeneralFunc.h"

void initCell(struct PoliceManager* manager, PrisonCell* cell) {
    do {
        int temp = getRandomNumber(MIN_CELL, MAX_CELL);
        if (!findCellByNum((PoliceManager*)manager, temp)) {
            cell->serialNumber = temp;
            break;
        }
    } while (1);
    cell->numOfCriminals = 0;
    cell->occupied = 0;
}

void printPrisonCell(const PrisonCell* cell) {
    printf("Serial Number: %d\n", cell->serialNumber);
    printf("Number of criminals in the cell: %d\n", cell->numOfCriminals);
    for (int i = 0; i < cell->numOfCriminals; i++) {
        printCriminal(&cell->criminals[i]);
        puts("");
    }
    printf("\n");
}