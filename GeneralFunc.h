#ifndef GENERAL
#define GENERAL

#define MAX_STR_LEN 255

char* getStr(const char* msg, int isItAName);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);
char* editName(char* str, int* valid);
int getRandomNumber(int min, int max);
void generalArrayFunction(const void* arr, int size, int typeSize, void(*func)(void* element));

#endif