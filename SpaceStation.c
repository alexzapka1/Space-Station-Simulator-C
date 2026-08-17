#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SpaceStation.h"

// Clear input buffer
void clearBuffer() {
    while (getchar() != '\n');
}

void initStation(SpaceStation* station, int r, int c, int crew_num) {
    station->rows = r;
    station->cols = c;
    station->crew_count = crew_num;
    station->events_head = NULL;

    station->grid = (int**)malloc(r * sizeof(int*));
    if (!station->grid) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < r; i++) {
        station->grid[i] = (int*)malloc(c * sizeof(int));
        if (!station->grid[i]) {
            printf("Memory allocation failed for grid row!\n");
            exit(1);
        }
        for (int j = 0; j < c; j++) {
            station->grid[i][j] = MAX_INTEGRITY;
        }
    }

    station->crew = (CrewMember*)malloc(crew_num * sizeof(CrewMember));
    if (!station->crew) {
        printf("Memory allocation failed for crew!\n");
        exit(1);
    }

    for (int i = 0; i < crew_num; i++) {
        sprintf(station->crew[i].name, "Astronaut_%d", i + 1);
        station->crew[i].health = 100;
    }
}

void addEvent(SpaceStation* station, const char* desc, int dmg) {
    EventNode* newNode = (EventNode*)malloc(sizeof(EventNode));
    if (!newNode) return;

    strcpy(newNode->description, desc);
    newNode->damage = dmg;
    newNode->next = NULL;

    if (station->events_head == NULL) {
        station->events_head = newNode;
    }
    else {
        EventNode* current = station->events_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void handleNextEvent(SpaceStation* station) {
    if (station->events_head == NULL) {
        printf("All clear! No emergencies to handle.\n");
        return;
    }

    EventNode* eventToHandle = station->events_head;
    station->events_head = station->events_head->next;

    printf("Handling Event: %s (Potential Damage: %d%%)\n", eventToHandle->description, eventToHandle->damage);

    int rand_row = rand() % station->rows;
    int rand_col = rand() % station->cols;

    station->grid[rand_row][rand_col] -= eventToHandle->damage;
    if (station->grid[rand_row][rand_col] < MIN_INTEGRITY) {
        station->grid[rand_row][rand_col] = MIN_INTEGRITY;
    }

    printf("Sector [%d][%d] took the hit. Current integrity: %d%%\n",
        rand_row, rand_col, station->grid[rand_row][rand_col]);

    free(eventToHandle);
}

void printStatus(SpaceStation* station) {
    PRINT_TITLE("STATION STATUS");
    printf("Sector Integrity Grid:\n");

    for (int i = 0; i < station->rows; i++) {
        for (int j = 0; j < station->cols; j++) {
            printf("[%3d%%] ", station->grid[i][j]);
        }
        printf("\n");
    }

    printf("\nCrew Members:\n");
    for (int i = 0; i < station->crew_count; i++) {
        printf("- %s (Health: %d)\n", station->crew[i].name, station->crew[i].health);
    }

    printf("\nPending Emergencies (Queue):\n");
    EventNode* current = station->events_head;
    int count = 1;
    if (!current) printf("None! Station is safe.\n");
    while (current != NULL) {
        printf("%d. %s (Dmg: %d)\n", count++, current->description, current->damage);
        current = current->next;
    }
}

void saveToFile(SpaceStation* station) {
    FILE* file = fopen(SAVE_FILENAME, "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "%d %d %d\n", station->rows, station->cols, station->crew_count);

    for (int i = 0; i < station->rows; i++) {
        for (int j = 0; j < station->cols; j++) {
            fprintf(file, "%d ", station->grid[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Station state saved successfully to '%s'.\n", SAVE_FILENAME);
}

void loadFromFile(SpaceStation* station) {
    FILE* file = fopen(SAVE_FILENAME, "r");
    if (!file) {
        printf("Error: Save file not found! Please save first.\n");
        return;
    }

    int r, c, crew_count;
    if (fscanf(file, "%d %d %d", &r, &c, &crew_count) != 3) {
        printf("Error reading file format.\n");
        fclose(file);
        return;
    }

    // Free existing memory before loading new data
    for (int i = 0; i < station->rows; i++) {
        free(station->grid[i]);
    }
    free(station->grid);
    free(station->crew);

    station->rows = r;
    station->cols = c;
    station->crew_count = crew_count;

    station->grid = (int**)malloc(r * sizeof(int*));
    if (!station->grid) { fclose(file); return; }

    for (int i = 0; i < r; i++) {
        station->grid[i] = (int*)malloc(c * sizeof(int));
        if (!station->grid[i]) { fclose(file); return; }

        for (int j = 0; j < c; j++) {
            if (fscanf(file, "%d", &station->grid[i][j]) != 1) {
                printf("Warning: corrupted save file data.\n");
            }
        }
    }

    station->crew = (CrewMember*)malloc(crew_count * sizeof(CrewMember));
    if (!station->crew) { fclose(file); return; }

    for (int i = 0; i < crew_count; i++) {
        sprintf(station->crew[i].name, "Astronaut_%d", i + 1);
        station->crew[i].health = 100;
    }

    fclose(file);
    printf("Station state loaded successfully.\n");
}

void freeStation(SpaceStation* station) {
    for (int i = 0; i < station->rows; i++) {
        free(station->grid[i]);
    }
    free(station->grid);
    free(station->crew);

    EventNode* current = station->events_head;
    while (current != NULL) {
        EventNode* temp = current;
        current = current->next;
        free(temp);
    }
}