#ifndef SPACESTATION_H
#define SPACESTATION_H

// --- Preprocessor Directives ---
#define MAX_NAME 50
#define MAX_DESC 100
#define MIN_INTEGRITY 0
#define MAX_INTEGRITY 100
#define SAVE_FILENAME "station_save.txt"

#define PRINT_TITLE(title) printf("\n=== %s ===\n", title)

// --- Structs ---

// Struct 1: Linked list node (Emergency event)
typedef struct EventNode {
    char description[MAX_DESC];
    int damage;
    struct EventNode* next;
} EventNode;

// Struct 2: Crew member
typedef struct {
    char name[MAX_NAME];
    int health;
} CrewMember;

// Struct 3: Space Station
typedef struct {
    int rows;
    int cols;
    int** grid;                 // Dynamic 2D array representing sectors
    CrewMember* crew;           // Dynamic array for crew members
    int crew_count;
    EventNode* events_head;     // Head of the linked list
} SpaceStation;

// --- Function Declarations ---
void initStation(SpaceStation* station, int r, int c, int crew_num);
void freeStation(SpaceStation* station);
void addEvent(SpaceStation* station, const char* desc, int dmg);
void handleNextEvent(SpaceStation* station);
void printStatus(SpaceStation* station);
void saveToFile(SpaceStation* station);
void loadFromFile(SpaceStation* station);
void clearBuffer();

#endif // SPACESTATION_H