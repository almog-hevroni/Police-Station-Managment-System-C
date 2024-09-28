#ifndef PRISONCELL
#define PRISONCELL

#include "Criminal.h"

#define MAX_CRIMINALS 2
#define MAX_CELL 10
#define MIN_CELL 1

struct PoliceManager;

typedef struct {
    int serialNumber;
    Criminal criminals[MAX_CRIMINALS];
    int numOfCriminals;
    int occupied;
}PrisonCell;


void initCell(struct PoliceManager* manager, PrisonCell* cell);
void printPrisonCell(const PrisonCell* cell);
#endif