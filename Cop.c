#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Cop.h"
#include "GeneralFunc.h"
#include "PoliceManager.h"
#include "Macros.h"

int initCop(Cop* cop, struct PoliceManager* manager) {
    cop->name = getStr("Enter the name of the cop:     ", 1);
    cop->numOfCriminals = 0;
    cop->id = getId(manager);
    cop->health = 100;
    Vehicle* v = ALLOCATE(Vehicle, 1);
    CHECK_NULL(v, 0);
    addVehicle(v, manager);
    cop->vehicle = v;
    getProficiency(cop);
    return 1;
}

void getProficiency(Cop* cop) {
    do {
        int num;
        printf("Please enter the proficiency of cop: \n0) Murder\n1) Drugs\n2) Theft\n");
        scanf("%d", &num);
        if (num >= 0 && num <= 2) {
            cop->proficiencyType = num;
            break;
        }
    } while (1);
}

int getId(struct PoliceManager* manager) {
    int id;
    do {
        puts("Please enter the id of the cop (id must be between 1-9999)");
        scanf("%d", &id);
        if (id < 1 || id > 9999) {
            puts("Wrong input, try again");
        }
        else if (findCopById(id, (PoliceManager*)manager) != NULL) {
            puts("Id already exists, try another one.");
        }
        else {
            return id;
        }
    } while (1);
}

void addVehicle(Vehicle* v, struct PoliceManager* manager) {
    initVehicle(v, manager);
}

void printCop(const Cop* cop) {
    printf("\nName: %s\nID: %d\nHealth: %d\nProficiency: %s\nNumber of Criminals caught: %d\n", cop->name, cop->id,
        cop->health, proficiency[cop->proficiencyType], cop->numOfCriminals);
    printVehicle(cop->vehicle);
}

void freeCopPtr(void* pCopPtr) {
    Cop* cop = *(Cop**)pCopPtr;
    if (cop != NULL) {
        SAFE_FREE(cop->name);
        free(cop);
    }
}

int addCriminalToCop(Cop* cop, Criminal* criminal) {
    if(cop->numOfCriminals == 0) {
		cop->criminals = (Criminal*)malloc(sizeof(Criminal));
		CHECK_NULL(cop->criminals, 0);
	}
    else if (cop->numOfCriminals > 0) {
        cop->criminals = (Criminal*)realloc(cop->criminals, (cop->numOfCriminals + 1) * sizeof(Criminal));
        if (!cop->criminals)
            return 0;
    }
    cop->criminals[cop->numOfCriminals] = *criminal;
    cop->numOfCriminals++;
    return 1;
}

int deleteCriminalFromCop(Cop* cop, int index) {
    if (index < cop->numOfCriminals - 1) {
        for (int i = index; i < cop->numOfCriminals - 1; i++) {
            cop->criminals[i] = cop->criminals[i + 1];
        }
    }
    cop->numOfCriminals--;
    Criminal* newCriminals = (Criminal*)realloc(cop->criminals, cop->numOfCriminals * sizeof(Criminal));
    CHECK_NULL(newCriminals, 0);
    cop->criminals = newCriminals;
    return 1;
}

void printCopPtr(const void* pCopPtr) {
    Cop* cop = *(Cop**)pCopPtr;
    printCop(cop);
}