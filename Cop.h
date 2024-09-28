#ifndef COP
#define COP

#include "Criminal.h"
#include "Vehicle.h"

typedef enum { eMurder, eDrugs, eTheft, eNoOfType } ProficiencyType;
static const char* proficiency[eNoOfType] = { "Murder","Drugs","Theft" };

struct PoliceManager; 

typedef struct {
    Criminal* criminals;
    char* name;
    int id;
    int health;
    Vehicle* vehicle;
    int numOfCriminals;
    ProficiencyType proficiencyType;
} Cop;

int initCop(Cop* cop, struct PoliceManager* manager);
void getProficiency(Cop* cop);
int getId(struct PoliceManager* manager);
void addVehicle(Vehicle* v, struct PoliceManager* manager);
void printCop(const Cop* cop);
void freeCopPtr(void* pCopPtr);
int addCriminalToCop(Cop* cop, Criminal* criminal);
int deleteCriminalFromCop(Cop* cop, int index);
void printCopPtr(const void* pCopPtr);

#endif