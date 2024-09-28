#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "GeneralFunc.h"
#include "Macros.h"


char* getStr(const char* msg, int isItAName)
{
    int validStr = 0;
    char* str;
    do {
        char temp[MAX_STR_LEN];
        printf("%s\t", msg);
        myGets(temp, MAX_STR_LEN);

        str = getDynStr(temp);
        if (isItAName == 1) {
            str = editName(str, &validStr);
        }
    } while (isItAName == 1 && !validStr);

    return str;
}

char* getDynStr(char* str)
{
    char* theStr;
    theStr = ALLOCATE(char, strlen(str) + 1);
    if (!theStr)
        return NULL;

    strcpy(theStr, str);
    return theStr;
}

char* myGets(char* buffer, int size)
{
    char* ok;
    if (buffer != NULL && size > 0)
    {
        do { //skip only '\n' strings
            ok = fgets(buffer, size, stdin);
        } while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
        if (ok)
        {
            char* back = buffer + strlen(buffer);
            //trim end spaces
            while ((buffer < back) && (isspace(*--back)));
            *(back + 1) = '\0';
            return buffer;
        }
        buffer[0] = '\0';
    }
    return NULL;
}

char* editName(char* str, int* valid) {
    int i, j;
    while (*str && *str == ' ') {
        str++;
    }
    if (strlen(str) <= 1) {
        puts("Name must be longer than 1");
        return NULL;
    }

    // Capitalize first letter of the string
    str[0] = toupper(str[0]);

    for (i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            puts("Please enter only letters");
            return NULL;
        }
        // If current character is a space and next character is a letter
        if (isspace(str[i]) && isalpha(str[i + 1])) {
            // Capitalize the next character
            str[i + 1] = toupper(str[i + 1]);
            // Skip to the end of the word
            while (isspace(str[i]))
                i++;
        }
    }
    // Remove consecutive spaces
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (!isspace(str[i]) || (i > 0 && !isspace(str[i - 1]))) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    *valid = 1;
    return str;
}

int getRandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void generalArrayFunction(const void* arr, int size, int typeSize, void(*func)(void* element))
{
    for (int i = 0; i < size; i++)
        func((char*)(arr)+i * typeSize);
}
