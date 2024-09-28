#ifndef _VEHICLE_
#define _VEHICLE_

typedef enum { eCar, eMotorcycle, eHorse, eNomOfType } VehicleType;
static const char* vehicle[eNomOfType] = { "Car", "Motorcycle", "Horse" };

struct PoliceManager;

typedef struct {
    int number;
    VehicleType type;
} Vehicle;

void initVehicle(Vehicle* v, struct PoliceManager* manager); 
int getNumOfVehicle(struct PoliceManager* manager); 
VehicleType getVehicleType();
void printVehicle(const Vehicle* v);

#endif