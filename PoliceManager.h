#ifndef POLICEMANAGER
#define POLICEMANAGER

#include "Cop.h"
#include "PrisonCell.h"
#include "list.h"


#define MAX_CELLS 10

typedef struct {
    Cop** cops;
    Criminal* criminals;
    LIST VehicleList;
    PrisonCell cells[MAX_CELLS];
    int copsCounter;
    int criminalCounter;
    int vehicleCounter;
    int cellCount;
}PoliceManager;

int initPoliceManager(PoliceManager* manager);
void createPrisonCells(PoliceManager* manager);
int addNewCop(PoliceManager* manager);
int addNewCriminal(PoliceManager* manager);
int addNewVehicle(PoliceManager* manager, Vehicle* v);
void addCriminalToPrisonCell(PoliceManager* manager, Criminal* criminal);
Cop* findCopById(const int id, PoliceManager* manager);
Vehicle* findVehicleByNum(const int num, PoliceManager* manager);
NODE* L_findVehicleByNum(PoliceManager* manager, NODE* pNode, const int num);
int findCellByNum(PoliceManager* manager, const int num);
Criminal* findCriminalByCode(const PoliceManager* manager,const char* code, int byType);
void sortCops(PoliceManager* manager,const int ask);
int compareCopsById(const void* a, const void* b);
int compareCopsByName(const void* a, const void* b);
int compareCopsByProficiency(const void* a, const void* b);
void findACop(PoliceManager* manager,const int choice);
void sendACopToMission(PoliceManager* manager);
Criminal* chooseCriminal(PoliceManager* manager);
Cop* chooseCop(PoliceManager* manager);
void attack(Cop* cop, Criminal* criminal);
void chooseAttackPowerForCop(Criminal* criminal, int* mediumHit, int* strongHit);
void criminalAttack(Cop* cop);
void printAttack();
void printPicture(const Cop* cop, const Criminal* criminal);
int printCaughtCriminals(const PoliceManager* manager);
void printAllCops(const PoliceManager* manager);
void printTheStation(const PoliceManager* manager);
void printAllCriminals(const PoliceManager* manager);
void printVehicles(const PoliceManager* manager);
void printPrisonCells(const PoliceManager* manager);
void printArrestedCriminals(PoliceManager* manager);
void sendCriminalToInvestigation(PoliceManager* manager);
Criminal* chooseCriminalToInvestigate(const PoliceManager* manager);
int chooseRandomQuestion();
int chooseAnswer(const int qNum);
void sendCriminalToJail(PoliceManager* manager, Criminal* criminal);
void deleteCopFromSystem(PoliceManager* manager, int id);
void deleteVehicle(Vehicle* theVehicle, NODE* pVehicleList);
int deleteCriminalFromSystem(PoliceManager* manager, char* code);
int findCriminalInPrisonCell(PoliceManager* manager, const Criminal* criminal);
void freeAllTheStation(PoliceManager* manager);
void freeAllCopsInStation(PoliceManager* manager);
void freeAllCriminalsInStation(PoliceManager* manager);
int saveSystemToBin(PoliceManager* manager);
int loadSystemFromBin(PoliceManager* manager);
int saveSystemToTXT(PoliceManager* manager);
int loadSystemFromTXT(PoliceManager* manager);

#endif