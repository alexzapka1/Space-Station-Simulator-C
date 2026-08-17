# Space Station Simulator 🚀

A console-based simulation game written entirely in C. This project was developed to demonstrate advanced C programming capabilities, specifically focusing on **Dynamic Memory Allocation**, **Custom Data Structures (Linked Lists & Structs)**, and **File I/O operations**.

## 🧠 Technical Highlights

* **Dynamic Memory Management:** Uses `malloc` and `free` to dynamically allocate memory for a 2D grid (sectors) and 1D arrays (crew members), ensuring zero memory leaks.
* **Linked Lists:** Implements a custom singly linked list to manage a queue of incoming emergency events.
* **Structs & Pointers:** Heavy use of structures and pointers to pass and modify the station's state across multiple modular functions.
* **File I/O:** Features persistent game states by reading from and writing to a text file (`station_save.txt`) using `fprintf` and `fscanf`.

## 🎮 Game Features

* **Interactive Menu:** Clean console UI with screen clearing and timed delays.
* **Sector Management:** A dynamic 2D grid representing the structural integrity of the station's sectors.
* **Emergency Queue:** Random events (e.g., Asteroid Strikes, Oxygen Leaks) are added to a pending queue and handled sequentially.
* **Save/Load System:** Save your current station's integrity and pending emergencies, and load them later to resume operations.

## 🛠️ Built With

* **Language:** C
* **Environment:** Visual Studio / Any standard C Compiler (GCC)

## 💻 Compilation & Execution

To compile the game using GCC, navigate to the project directory in your terminal and run:

```bash
gcc main.c SpaceStation.c -o SpaceStation
./SpaceStation
```
