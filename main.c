#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "PoliceManager.h"

int main() {
    srand((int)time(NULL));
    PoliceManager manager;
    if (!initPoliceManager(&manager))
        puts("Error creating PoliceManager!");

    int choice;

    do {
        puts("====Menu====");
        puts("1. Load station from binary file.");
        puts("2. Load station from txt file");
        puts("3. Print the station.");
        puts("4. Print the arrested criminals.");
        puts("5. Add a new cop to the system.");
        puts("6. Open a new Criminal.");
        puts("7. Sort cops.");
        puts("8. Find a cop.");
        puts("9. Send a cop to a mission!");
        puts("10. Send a criminal to an investigation!");
        puts("11. exit.");

        scanf("%d", &choice);
        switch (choice) {
        case 1:
            loadSystemFromBin(&manager);
            break;
        case 2:
            loadSystemFromTXT(&manager);
            break;
        case 3:
            printTheStation(&manager);
            break;
        case 4:
            printArrestedCriminals(&manager);
            break;
        case 5:
            if (!addNewCop(&manager))
                puts("Error adding Cop");
            else
                puts("Welcome to our force!\n");
            break;
        case 6:
            if (!addNewCriminal(&manager))
                puts("Error adding Criminal\n");
            else
                puts("We'll catch you!\n");
            break;
        case 7:
            sortCops(&manager, -1);
            printAllCops(&manager);
            puts("");
            break;
        case 8:
            if (manager.copsCounter != 0) {
                do {
                    int findBy;
                    puts("Please enter the type of search: \n1)By ID\n2)By name\n3)By Proficiency");
                    scanf("%d", &findBy);
                    if (findBy >= 1 && findBy <= 3) {
                        sortCops(&manager, findBy);
                        findACop(&manager, findBy);
                        break;
                    }
                } while (1);
            }
            else {
                puts("No cops to find, add cops first.\n");
            }

            break;
        case 9:
            sendACopToMission(&manager);
            break;
        case 10:
            sendCriminalToInvestigation(&manager);
            break;
        case 11:
            puts("Bye bye!");
            saveSystemToBin(&manager);
            saveSystemToTXT(&manager);
            freeAllTheStation(&manager);
            break;
        default:
            puts("Wrong choice!");
            break;

        }

    } while (choice != 11);

    return 0;

}