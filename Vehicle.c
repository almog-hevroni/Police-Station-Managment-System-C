#include <stdio.h>

#include "Vehicle.h"
#include "PoliceManager.h"

void  initVehicle(Vehicle* v, struct PoliceManager* manager) {
    v->number = getNumOfVehicle(manager);
    v->type = getVehicleType();
    addNewVehicle((PoliceManager*)manager, v);
}

int getNumOfVehicle(struct PoliceManager* manager) {
    int temp;
    do {
        puts("Enter the number of the vehicle 1-50");
        scanf("%d", &temp);
        if (temp < 1 || temp > 50)
            puts("Error! try again.");
        else if (findVehicleByNum(temp, (PoliceManager*)manager))
            puts("Number already exists, try another one!");
        else
            return temp;
    } while (1);
}

VehicleType getVehicleType() {
    do {
        puts("What type of vehicle would you like?");
        int type;
        for (int i = 0; i < eNoOfEvidence; i++) {
            printf("%d) %s\n", i, vehicle[i]);
        }
        scanf("%d", &type);

        if (type < 0 || type > 2)
            puts("Error! try again.");
        else return (VehicleType)type;
    } while (1);
}


void printVehicle(const Vehicle* v) {
    printf("Vehicle type: %s\nVehicle number: %d\n", vehicle[v->type], v->number);
}