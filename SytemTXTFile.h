#ifndef _SYTEMTXTFILE_
#define _SYTEMTXTFILE_

#include "PoliceManager.h"
#include "Date.h"

int saveSystemTXT(const PoliceManager* manager, const char* systemBin);
int loadSystemStateToTXT(PoliceManager* manager, const char* filename);
#endif