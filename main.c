#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Library for Sleep
#include "SpaceStation.h"

int main() {
    SpaceStation myStation;
    int choice;

    srand((unsigned int)time(NULL));

    initStation(&myStation, 3, 3, 2);

    addEvent(&myStation, "Asteroid Strike", 25);
    addEvent(&myStation, "Oxygen Leak", 15);

    do {
        system("cls"); // Clear screen for a clean UI

        PRINT_TITLE("SPACE STATION SIMULATOR - MAIN MENU");
        printf("1. View Station Status\n");
        printf("2. Handle Next Emergency (Dequeue Event)\n");
        printf("3. Trigger Random Emergency\n");
        printf("4. Save Station State\n");
        printf("5. Load Station State\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            Sleep(2000); // Wait 2 seconds for user to read error
            continue;
        }

        switch (choice) {
        case 1:
            system("cls"); // Clear menu before showing status
            printStatus(&myStation);
            printf("\nPress Enter to return to menu...");
            clearBuffer(); // Clear leftover inputs
            getchar();     // Wait for user to press Enter
            break;
        case 2:
            printf("\n");
            handleNextEvent(&myStation);
            Sleep(2500); // Wait 2.5 seconds to read result
            break;
        case 3:
            addEvent(&myStation, "System Malfunction", rand() % 30 + 10);
            printf("\n[ALERT] A new emergency has been detected and added to the queue!\n");
            Sleep(2000);
            break;
        case 4:
            printf("\n");
            saveToFile(&myStation);
            Sleep(1500);
            break;
        case 5:
            printf("\n");
            loadFromFile(&myStation);
            Sleep(1500);
            break;
        case 6:
            printf("\nExiting simulation. Shutting down systems...\n");
            Sleep(1500);
            break;
        default:
            printf("\nInvalid choice. Try again.\n");
            Sleep(1500);
        }
    } while (choice != 6);

    freeStation(&myStation);
    return 0;
}