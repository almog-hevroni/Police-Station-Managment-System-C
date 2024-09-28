#ifndef _FILEHELPERTXT_
#define _FILEHELPERTXT_

#include <stdio.h>
#include "PoliceManager.h"

void saveStringTXT(FILE* file,const char* str);
void saveCriminalRecordTXT(FILE* file, const CriminalRecord* record);
void saveEvidenceTXT(FILE* file, const Evidence* theEvidence);
void saveDateTXT(FILE* file,const Date* date);
void saveVehiclesTXT(FILE* file, const LIST* vehicleList, const PoliceManager* manager);
void savePrisonCellsTXT(FILE* file, const PrisonCell* cells, const int cellCount);

char* loadStringTXT(FILE* file);
Criminal* loadCriminalTXT(FILE* file);
void loadCriminalsTXT(FILE* file, PoliceManager* manager);
void loadVehiclesTXT(PoliceManager* manager, FILE* file);
void loadPrisonCellTXT(PoliceManager* manager, FILE* file, PrisonCell* cell);
void loadCriminalRecordTXT(FILE* file, CriminalRecord* record);
void loadEvidenceTXT(FILE* file, Evidence* theEvidence);
void loadDateTXT(FILE* file, Date* date);

#endif