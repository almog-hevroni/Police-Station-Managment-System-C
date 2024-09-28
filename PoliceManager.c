
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "PoliceManager.h"
#include "GeneralFunc.h"
#include "Macros.h"
#include "SystemBin.h"
#include "SytemTXTFile.h"

int initPoliceManager(PoliceManager* manager) {
    manager->cops = NULL;
    manager->criminals = NULL;
    if (!L_init(&manager->VehicleList))
        return 0;
    manager->copsCounter = 0;
    manager->criminalCounter = 0;
    manager->vehicleCounter = 0;
    manager->cellCount = 0;
    createPrisonCells(manager);
    return 1;
}

int addNewCop(PoliceManager* manager) {
    Cop* pCop = (Cop*)calloc(1, sizeof(Cop));
    CHECK_NULL(pCop, 0);

    initCop(pCop, (struct PoliceManager*)manager);

    manager->cops = (Cop**)realloc(manager->cops, (manager->copsCounter + 1) * sizeof(Cop*));
    if (!manager->cops) {
        freeCopPtr(pCop);
        return 0;
    }
    manager->cops[manager->copsCounter] = pCop;
    manager->copsCounter++;
    return 1;
}

int addNewCriminal(PoliceManager* manager) {
    manager->criminals = (Criminal*)realloc(manager->criminals, (manager->criminalCounter + 1) * sizeof(Criminal));
    if (!manager->criminals)
        return 0;

    initCriminal(&manager->criminals[manager->criminalCounter], (struct PoliceManager*)manager);
    manager->criminalCounter++;
    return 1;
}

Cop* findCopById(const int id, PoliceManager* manager) {
    if (manager->copsCounter == 0)
        return NULL;
    for (int i = 0; i < manager->copsCounter; i++) {
        if (id == manager->cops[i]->id)
            return manager->cops[i];
    }
    return NULL;
}

Vehicle* findVehicleByNum(const int num, PoliceManager* manager) {
    if (manager->vehicleCounter == 0)
        return 0;

    NODE* currentNode = L_findVehicleByNum(manager, manager->VehicleList.head.next, num);
    if (currentNode != NULL)
        return currentNode->key;

    return NULL;
}

NODE* L_findVehicleByNum(PoliceManager* manager, NODE* pNode, const int num) {
    NODE* tmp = pNode;

    for (int i = 0; i < manager->vehicleCounter; i++) {
        Vehicle* v = (Vehicle*)tmp->key;
        if (v->number == num)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

int addNewVehicle(PoliceManager* manager, Vehicle* v) {
    NODE* newNode = manager->VehicleList.head.next; //first node
    NODE* pPrevNode = &manager->VehicleList.head; //head of the list
    while (newNode != NULL) {
        if (newNode->next == NULL) {
            if (!L_insert(newNode, v)) {
                return 0;
            }
            else
            {
                manager->vehicleCounter++;
                return 1;
            }
        }
        pPrevNode = newNode;
        newNode = newNode->next;
    }

    if(!L_insert(pPrevNode, v)) {
		return 0;
	}

    manager->vehicleCounter++;

    return 1;
}

void createPrisonCells(PoliceManager* manager) {
    for (int i = 0; i < MAX_CELLS; i++) {
        initCell((struct PoliceManager*)manager, &manager->cells[i]);
        manager->cellCount++;
    }
}

int findCellByNum(PoliceManager* manager, const int num) {
    for (int i = 0; i < manager->cellCount; i++) {
        if (manager->cells[i].serialNumber == num)
            return 1;
    }
    return 0;
}


void sortCops(PoliceManager* manager, const int ask) {
    int choice;
    int (*compare)(const void* cop1, const void* cop2) = NULL;
    if (ask != -1) {
        choice = ask;
    }
    if (manager->copsCounter == 0) {
        puts("No cops to sort. Please add cops to the system.\n");
        return;
    }
    do {
        if (ask == -1) {
            puts("Please enter the type of the sort: \n1) By ID\n2)By name\n3)By proficiency");
            scanf("%d", &choice);

            if (choice < 1 || choice > 3) {
                puts("Wrong input! Try again!");
                continue;
            }
        }
        break;
    } while (1);
    switch (choice) {
    case 1:
        compare = compareCopsById;
        break;
    case 2:
        compare = compareCopsByName;
        break;
    case 3:
        compare = compareCopsByProficiency;
        break;
    default:
        puts("Invalid choice");
        break;
    }
    qsort(manager->cops, manager->copsCounter, sizeof(Cop*), compare);
}

int compareCopsById(const void* a, const void* b) {
    Cop* copA = *(Cop**)a;
    Cop* copB = *(Cop**)b;
    return copA->id - copB->id;
}

int compareCopsByName(const void* a, const void* b) {
    Cop* copA = *(Cop**)a;
    Cop* copB = *(Cop**)b;
    return strcmp(copA->name, copB->name);
}

int compareCopsByProficiency(const void* a, const void* b) {
    Cop* copA = *(Cop**)a;
    Cop* copB = *(Cop**)b;
    return (copA->proficiencyType - copB->proficiencyType);
}


void printAllCops(const PoliceManager* manager) {
    generalArrayFunction(manager->cops, manager->copsCounter, sizeof(Cop*), (void (*)(void*)) printCopPtr);
}

void findACop(PoliceManager* manager,const int choice) {
    int (*compare)(const void* cop1, const void* cop2) = NULL;
    Cop c = { 0 };
    Cop* pCop = &c;

    switch (choice) {
    case 1:
        puts("Please enter the id of the cop:");
        scanf("%d", &c.id);
        compare = compareCopsById;
        break;

    case 2:
        c.name = getStr("Enter the name of the cop:     ", 1);
        compare = compareCopsByName;
        break;
    case 3:
        do {
            int num;
            printf("Please enter the proficiency of the cop: \n0) Murder\n1) Drugs\n2) Theft\n");
            scanf("%d", &num);
            if (num >= 0 && num <= 3) {
                c.proficiencyType = num;
                compare = compareCopsByProficiency;
                break;
            }
        } while (1);

        break;
    }

    if (compare != NULL) {
        Cop** pC = bsearch(&pCop, manager->cops, manager->copsCounter, sizeof(Cop*), compare);
        if (pC == NULL) {
            puts("Cop not found\n");
        }
        else {
            puts("Cop found:");
            printCop(*pC);
            puts("");
        }
    }
}

int printKnownCriminals(PoliceManager* manager) {
    int count = 0;
    for (int i = 0; i < manager->criminalCounter; i++) {
        if (manager->criminals[i].type == 0) {
            printCriminal(&manager->criminals[i]);
            count++;
        }
    }
    return count;
}

Criminal* findCriminalByCode(const PoliceManager* manager, const char* code, int byType) {
    for (int i = 0; i < manager->criminalCounter; i++) {
        if (byType == 1) {
            if (strcmp(manager->criminals[i].record.caseCode, code) == 0 &&
                manager->criminals[i].type == eKnown) {
                return &manager->criminals[i];
            }
        }
        else {
            if (strcmp(manager->criminals[i].record.caseCode, code) == 0)
                return &manager->criminals[i];
        }
    }
    return NULL;
}


void sendACopToMission(PoliceManager* manager) {
    if (manager->copsCounter == 0 || manager->criminalCounter == 0) {
        puts("Must be at least one Cop and one Criminal!");
        return;
    }
    Criminal* criminal = chooseCriminal(manager);
    if (criminal == NULL)
        return;
    Cop* cop = chooseCop(manager);

    attack(cop, criminal);

    if (cop->health <= 0) {
        puts("Criminal got away! Cop is fired!\n");
        deleteCopFromSystem(manager, cop->id);
        manager->vehicleCounter--;
        criminal->health = 100;
    }
    else {
        criminal->type = eCaught;
        if (addCriminalToCop(cop, criminal)) {
            puts("Criminal caught! You can investigate him now!\n");
            criminal->health = 50;
            cop->health = 100;
        }
    }
}


Criminal* chooseCriminal(PoliceManager* manager) {
    char code[CODE_LEN + 1];
    Criminal* criminal;
    do {
        if (printKnownCriminals(manager) == 0) {
            puts("No criminals to catch!");
            return NULL;
        }
        else {
            printf("\n");
            puts("Please choose a Criminal by Criminal record code:");

            myGets(code, CODE_LEN + 1);
            criminal = findCriminalByCode(manager, code, 1);
            if (criminal != NULL)
                break;
            else
                puts("Criminal not found.");
        }
    } while (1);
    return criminal;
}

Cop* chooseCop(PoliceManager* manager) {
    int tempId;
    Cop* cop;
    do {
        printAllCops(manager);
        puts("Please choose a Cop by id for the mission:\n");
        scanf("%d", &tempId);
        cop = findCopById(tempId, manager);
        if (cop != NULL)
            break;
        else
            puts("Cop not found.");
    } while (1);
    printf("\n");
    return cop;
}

void attack(Cop* cop, Criminal* criminal) {
    int mediumHit = 3;
    int strongHit = 2;
    while (cop->health > 0 && criminal->health > 0) {
        printPicture(cop, criminal);
        chooseAttackPowerForCop(criminal, &mediumHit, &strongHit);
        printAttack();
        criminalAttack(cop);
        printf("You've been hit!!!!\n");
        printAttack();
    }
    printCop(cop);
    printf("\n");
    printCriminal(criminal);
    printf("\n");
}

void printPicture(const Cop* cop, const Criminal* criminal) {
    printf("\n\n");
    printf("   ___/\\___\n");
    printf("    ( >_< )        ( >_< )\n");
    printf("       |              |\n");
    printf("      /|\\            /|\\\n");
    printf("       |              |\n");
    printf("      / \\            / \\\n");
    printf("   ==COP:%d==    ==CRIMINAL:%d==\n", cop->health, criminal->health);
}

void chooseAttackPowerForCop(Criminal* criminal, int* mediumHit, int* strongHit) {
    int stop = 0;
    int power;
    do {
        printf("Choose the attack power of the cop:\n1) Power 5 - Unlimited\n2) Power 10- Max 3 times\n3) Power 20 - Max 2 times.\n");
        scanf("%d", &power);
        switch (power) {
        case 1:
            criminal->health -= 5;
            stop = 1;
            break;
        case 2:
            (*mediumHit)--;
            if (*mediumHit >= 0) {
                criminal->health -= 10;
                stop = 1;
            }
            else {
                puts("Cop is too tired for this hit.");
            }
            break;
        case 3:
            (*strongHit)--;
            if (*strongHit >= 0) {
                criminal->health -= 20;
                stop = 1;
            }
            else {
                puts("Cop is too tired for this hit.");
            }
            break;
        default:
            puts("Attack power not valid.");
        }
    } while (stop == 0);
}

void criminalAttack(Cop* cop) {
    int attack = getRandomNumber(5, 8);
    cop->health -= attack;
}

void printAttack() {
    int print = getRandomNumber(1, 5);
    switch (print) {
    case 1:
        printf("  ________\n");
        printf(" /        \\\n");
        printf("/  BOOM!!  \\\n");
        printf("\\__________/\n");
        break;
    case 2:
        printf("  _________\n");
        printf(" /          \\\n");
        printf("/    POW!    \\\n");
        printf("\\¯¯¯¯¯¯¯¯¯¯/\n");
        break;
    case 3:
        printf("  ________\n");
        printf(" /   /¯\\   \\\n");
        printf("/  SMACK!  \\\n");
        printf("\\__________\\\n");
        break;
    case 4:
        printf("  ________\n");
        printf(" /  /\\  \\ \\\n");
        printf("/  OUCH!  \\\n");
        printf("\\_________/¯\n");
        break;
    case 5:
        printf("  ________\n");
        printf(" /   /¯¯¯\\  \\\n");
        printf("/  KAPOW!  \\\n");
        printf("\\__________/\n");
        break;
    default:
        printf("  ________\n");
        printf(" /   __   \\\n");
        printf("/   ZING!  \\\n");
        printf("\\_______/¯¯\n");
        break;
    }
}

void deleteCopFromSystem(PoliceManager* manager, int id) {
    int indexToDelete = -1;

    for (int i = 0; i < manager->copsCounter; i++) {
        if (id == manager->cops[i]->id) {
            indexToDelete = i;
            deleteVehicle(manager->cops[i]->vehicle, (NODE*) & manager->VehicleList);
            break;
        }
    }

    if (indexToDelete == -1) {
        return;
    }

    free(manager->cops[indexToDelete]);
    manager->cops[indexToDelete] = manager->cops[manager->copsCounter - 1];
    manager->copsCounter--;

    Cop** newCops = (Cop**)malloc(manager->copsCounter * sizeof(Cop*));
    if (newCops == NULL) {
        // Handle allocation failure
        return;
    }

    for (int i = 0; i < manager->copsCounter; i++) {
        newCops[i] = manager->cops[i];
    }

    free(manager->cops);

    manager->cops = newCops;
}

void deleteVehicle(Vehicle* theVehicle, NODE* pVehicleList) {
    // Check for null pointers
    if (theVehicle == NULL || pVehicleList == NULL || pVehicleList == NULL) {
        return;
    }

    NODE* current = pVehicleList;
    NODE* previous = NULL;

    while (current != NULL) {
        Vehicle* currentVehicle = (Vehicle*)current->key;

        if (currentVehicle == theVehicle) {
            if (previous == NULL) {
                pVehicleList = current->next;
            }
            else {
                previous->next = current->next;
            }

            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}





int printCaughtCriminals(const PoliceManager* manager) {
    int caught = 0;
    for (int i = 0; i < manager->criminalCounter; i++) {
        if (manager->criminals[i].type == eCaught) {
            printCriminal(&manager->criminals[i]);
            caught++;
        }
    }
    return caught;
}

void sendCriminalToInvestigation(PoliceManager* manager) {
    char* code;
    Criminal* criminal;
    if (manager->criminals == 0) {
        puts("There's no Criminals in the system!\n");
        return;
    }
    if (printCaughtCriminals(manager) == 0) {
        puts("There's no caught Criminals in the system!\n");
        return;
    }
    int rightAnswers = 0;
    criminal = chooseCriminalToInvestigate(manager);
    code = criminal->record.caseCode;

    for (int i = 0; i < 5; i++) {
        rightAnswers += chooseRandomQuestion();
    }
    if (rightAnswers >= 2) {
        puts("The criminal is free of guilt! Criminal deleted from the system");
        deleteCriminalFromSystem(manager, code);
    }
    else {
        puts("The criminal is guilty and goes to jail!!");
        sendCriminalToJail(manager, criminal);
        puts("");
    }
}

Criminal* chooseCriminalToInvestigate(const PoliceManager* manager) {
    char code[CODE_LEN + 1];
    Criminal* criminal;
    do {
        puts("");
        puts("Please enter the record code of the criminal:");
        myGets(code, CODE_LEN + 1);
        criminal = findCriminalByCode(manager, code, 0);
        if (criminal != NULL && criminal->type == eCaught)
            break;
        else if (criminal != NULL && criminal->type != eCaught)
            puts("Criminal is not caught! You can't investigate him!");
        else
            puts("Criminal not found.");
    } while (1);
    return criminal;
}


int chooseRandomQuestion() {
    int random = getRandomNumber(1, 10);
    switch (random) {
    case 1:
        puts("Can you provide your whereabouts during the time of the crime?");
        break;
    case 2:
        puts("Do you have an alibi or witnesses who can confirm your location?");
        break;
    case 3:
        puts("Were you aware of anyone who had a motive to commit the crime?");
        break;
    case 4:
        puts("Did you have any interactions with the victim prior to the incident?");
        break;
    case 5:
        puts("Do you own any weapons or tools that could have been used in the commission of the crime?");
        break;
    case 6:
        puts("Are there any surveillance cameras or witnesses that might have captured your actions?");
        break;
    case 7:
        puts("Can you account for any unusual behavior or actions on the day of the crime?");
        break;
    case 8:
        puts("Have you been involved in similar incidents or criminal activities in the past?");
        break;
    case 9:
        puts("Can you provide any financial or personal reasons why you might be suspected of the crime?");
        break;
    case 10:
        puts("Is there any physical evidence that might link you to the scene of the crime, such as fingerprints or DNA?");
        break;
    }
    return chooseAnswer(random);
}

int chooseAnswer(const int qNum) {
    int rightAnswer = getRandomNumber(1, 3);
    int answer;
    int isTheAnswerValid = 0;
    do {
        switch (qNum) {
        case 1:
            puts("1) I was at work until late evening, then I went straight home and stayed there for the rest of the night.");
            puts("2) I went out for dinner with some friends, then we went to a movie. After that, I returned home around midnight.");
            puts("3) I was at the gym for a couple of hours, then I grabbed some takeout and went back to my apartment.");
            break;
        case 2:
            puts("1) Yes, I was with my family at a birthday party. My parents, siblings, and several relatives can confirm I was there all night.");
            puts("2) I was at my girlfriend's place. She can vouch for me. We watched movies together until late.");
            puts("3) I was volunteering at a homeless shelter. There were plenty of other volunteers and staff who saw me there.");
            break;
        case 3:
            puts("1) I can't think of anyone who would want to harm the victim. They were well-liked in the community.");
            puts("2) There were rumors about a business rival having issues with the victim, but I have no concrete evidence.");
            puts("3) I heard the victim had some disputes with neighbors, but nothing serious enough to lead to this.");
            break;
        case 4:
            puts("1) I've seen the victim around the neighborhood, but I never really spoke to them. We were just acquaintances.");
            puts("2) I knew the victim from work, but we never had any personal interactions outside of office meetings.");
            puts("3) The victim was a regular at the cafe I work at, but our interactions were limited to taking orders and small talk.");
            break;
        case 5:
            puts("1) No, I don't own any weapons. I'm not into hunting or anything like that.");
            puts("2) I own a hunting rifle, but it's securely locked away in a safe. It hasn't been touched in years.");
            puts("3) I have some basic tools in my garage, but nothing that could be used as a weapon. They're just for household repairs.");
            break;
        case 6:
            puts("1)Yes, there are security cameras at my workplace. They should show that I was there the entire time.");
            puts("2) My neighbor has a security camera that faces my front door. They can confirm when I left and returned home.");
            puts("3) I was at a crowded restaurant for most of the evening. There were plenty of witnesses who saw me there.");
            break;
        case 7:
            puts("1) I can't think of anything unusual. It was a regular day for me, just like any other.");
            puts("2) I was feeling sick that day, so I left work early and went straight home to rest.");
            puts("3) I had a fight with my roommate, but it was nothing serious. We argue sometimes, but it's never escalated.");
            break;
        case 8:
            puts("1) No, I have a clean record. I've never been involved in any criminal activities.");
            puts("2) I got a speeding ticket once, but that's the extent of my involvement with the law.");
            puts("3) I was falsely accused of shoplifting once, but the charges were dropped. I've learned my lesson since then.");
            break;
        case 9:
            puts("1) I can't think of any reason why I would be suspected. I barely knew the victim.");
            puts("2) I had a disagreement with the victim a while back, but it was nothing serious. We moved on from it.");
            puts("3) I recently had some financial troubles, but nothing that would drive me to commit a crime. I'm trying to get back on track.");
            break;
        case 10:
            puts("1) No, I've never been to the scene of the crime. There shouldn't be any evidence linking me there.");
            puts("2) I might have visited the area before, but there's no reason for my fingerprints or DNA to be found at the scene.");
            puts("3) I did visit the scene of the crime earlier that day, but I didn't touch anything. There shouldn't be any evidence of my presence.");
            break;
        }
        scanf("%d", &answer);
        if (answer < 1 || answer > 3) {
            puts("Wrong input, try again!");
        }
        else {
            break;
        }
    } while (1);
    if (answer == rightAnswer) {
        isTheAnswerValid = 1;
    }
    return isTheAnswerValid;
}

int deleteCriminalFromSystem(PoliceManager* manager, char* code) {
    for (int i = 0; i < manager->copsCounter; i++) {
        for (int j = 0; j < manager->cops[i]->numOfCriminals; j++) {
            if (strcmp(manager->cops[i]->criminals[j].record.caseCode, code) == 0) {
                deleteCriminalFromCop(manager->cops[i], j);
                break;
            }
        }
    }
    for (int i = 0; i < manager->criminalCounter; i++) {
        if (strcmp(manager->criminals[i].record.caseCode, code) == 0) {
            freeCriminal(&manager->criminals[i]);
            for (int k = i; k < manager->criminalCounter - 1; k++) {
                manager->criminals[k] = manager->criminals[k + 1];
            }
            manager->criminalCounter--;
            Criminal* newCriminals = (Criminal*)realloc(manager->criminals,
                manager->criminalCounter * sizeof(Criminal));
            CHECK_NULL(newCriminals, 0);
            manager->criminals = newCriminals;
            break;
        }
    }
    return  1;
}

void sendCriminalToJail(PoliceManager* manager, Criminal* criminal) {
    criminal->type = eArrested;
    addCriminalToPrisonCell(manager, criminal);
}

void addCriminalToPrisonCell(PoliceManager* manager, Criminal* criminal) {
    for (int i = 0; i < MAX_CELLS; i++) {
        PrisonCell* currentCell = &(manager->cells[i]);
        if (currentCell->numOfCriminals < MAX_CRIMINALS) {
            for (int j = 0; j < MAX_CRIMINALS; j++) {
                if (currentCell->occupied == 0) {
                    currentCell->criminals[currentCell->numOfCriminals] = *criminal;
                    currentCell->numOfCriminals++;
                    printf("Criminal with code %s added to cell %d\n", criminal->record.caseCode,
                        currentCell->serialNumber);
                    if (currentCell->numOfCriminals == 2)
                        currentCell->occupied = 1;
                    return;
                }
            }
        }
    }
    printf("All prison cells are full. Unable to add criminal to any cell.\n");
}

void printArrestedCriminals(PoliceManager* manager) {
    int arrestNum = 0;
    for (int i = 0; i < manager->criminalCounter; i++) {
        Criminal* currentCriminal = &(manager->criminals[i]);
        if (currentCriminal->type == eArrested) {
            printCriminal(currentCriminal);
            printf("In cell %d", findCriminalInPrisonCell(manager, currentCriminal));
            printf("\n");
            arrestNum++;
        }
    }
    if (arrestNum == 0) {
        printf("There is no arrested criminals at the station");
    }
    puts("");
}

int findCriminalInPrisonCell(PoliceManager* manager, const Criminal* criminal) {
    for (int i = 0; i < MAX_CELLS; i++) {
        PrisonCell* currentCell = &(manager->cells[i]);
        for (int j = 0; j < MAX_CRIMINALS; j++) {
            if (currentCell->occupied == 0) {
                if (strcmp(currentCell->criminals[j].record.caseCode, criminal->record.caseCode) == 0) {
                    return currentCell->serialNumber;
                }
            }
        }
    }
    return -1;
}

void printTheStation(const PoliceManager* manager) {
    puts("====Cops====");
    printAllCops(manager);
    puts("");
    puts("====Criminals====");
    printAllCriminals(manager);
    puts("");
    puts("====Vehicles====");
    printVehicles(manager);
    puts("");
    puts("====Prison Cells====");
    printPrisonCells(manager);
}

void printAllCriminals(const PoliceManager* manager) {
    generalArrayFunction(manager->criminals, manager->criminalCounter, sizeof(Criminal),
        (void (*)(void*)) printCriminal);
}


void printVehicles(const PoliceManager* manager) {
    L_print(&manager->VehicleList,printVehicle);
}

void printPrisonCells(const PoliceManager* manager) {
    generalArrayFunction(manager->cells, manager->cellCount, sizeof(PrisonCell), (void (*)(void*)) printPrisonCell);
}

void freeAllTheStation(PoliceManager* manager) {
    freeAllCopsInStation(manager);
    free(manager->cops);
    freeAllCriminalsInStation(manager);
    free(manager->criminals);
    L_free(&manager->VehicleList, free);
}

void freeAllCopsInStation(PoliceManager* manager) {
    generalArrayFunction(manager->cops, manager->copsCounter, sizeof(Cop*), (void (*)(void*)) freeCopPtr);
}

void freeAllCriminalsInStation(PoliceManager* manager) {
    generalArrayFunction(manager->criminals, manager->criminalCounter, sizeof(Criminal), (void (*)(void*)) freeCriminal);
}

int saveSystemToBin(PoliceManager* manager) {
    if (!saveSystem(manager, "systemData.bin")) {
        return 0;
    }
    return 1;
}

int loadSystemFromBin(PoliceManager* manager) {
    if (!loadSystemState(manager, "systemData.bin")) {
        return 0;
    }
    return 1;
}

int saveSystemToTXT(PoliceManager* manager) {
    if (!saveSystemTXT(manager, "systemTXT.txt")) {
        return 0;
    }
    return 1;
}

int loadSystemFromTXT(PoliceManager* manager) {
    if (!loadSystemStateToTXT(manager, "systemTXT.txt")) {
        return 0;
    }
    return 1;
}