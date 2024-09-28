#ifndef _FILEHELPER_
#define _FILEHELPER_

#include "PoliceManager.h"

void saveString(FILE* file, const char* str);
void saveCriminalRecord(FILE* file, const CriminalRecord* record);
void saveEvidence(FILE* file, const Evidence* theEvidence);
void saveDate(FILE* file, const Date* date);
void saveVehiclesCompressed(FILE* file, const LIST* vehicleList,  const PoliceManager* manager);
void savePrisonCells(FILE* file, const PrisonCell* cells, const int cellCount);

char* loadString(FILE* file);
Criminal* loadCriminal(FILE* file);
void loadCriminals(FILE* file, PoliceManager* manager);
void loadVehiclesCompressed(PoliceManager* manager, FILE* file);
void loadPrisonCell(PoliceManager* manager, FILE* file, PrisonCell* cell);
void loadCriminalRecord(FILE* file, CriminalRecord* record);
void loadEvidence(FILE* file, Evidence* theEvidence);
void loadDate(FILE* file, Date* date);
#endif