#ifndef _SYSTEMBIN_
#define _SYSTEMBIN_

#include <stdio.h>
#include "PoliceManager.h"

int saveSystem(const PoliceManager* manager, const char* systemBin);
int loadSystemState(PoliceManager* manager, const char* filename);

#endif