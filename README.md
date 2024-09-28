# Police Station Management Simulation

## Overview

This Police Station Management Simulation is a comprehensive C program that models the operations of a police station. It demonstrates advanced programming concepts and system design principles, providing a realistic simulation of law enforcement management.

## Key Features

- **Modular System Design**: Ensures maintainability and scalability of the codebase.
- **Advanced Data Structures**: Utilizes linked lists and dynamic arrays for efficient data management.
- **File I/O Handling**: Implements both binary and text-based file operations for data persistence.
- **Dynamic Memory Management**: Optimizes resource usage through careful allocation and deallocation.
- **Criminal Database**: Manages detailed criminal records and evidence.
- **Intuitive User Interface**: Offers a menu-driven interface for easy navigation and operation.
- **Performance Optimization**: Implements efficient algorithms for system operations.

## Components

1. **PoliceManager**: Central component managing all aspects of the police station.
2. **Cop**: Represents police officers with attributes like name, ID, health, and proficiency.
3. **Criminal**: Manages criminal data including records and status.
4. **Vehicle**: Handles different types of police vehicles.
5. **PrisonCell**: Simulates prison cells with capacity and occupancy management.
6. **Evidence**: Tracks different types of evidence related to criminal cases.

## Main Functionalities

- Add and manage cops and criminals
- Conduct investigations and missions
- Manage vehicles and prison cells
- Sort and search functionalities for cops and criminals
- Save and load system state (binary and text formats)

## How to Use

1. Open the project in your preferred C development environment (e.g., Visual Studio, Code::Blocks, or a text editor with a C compiler).
2. Build the solution to compile the project.
3. Run the program from within your development environment or navigate to the output directory and run the executable.
4. Follow the on-screen menu to interact with the system. The main menu options include:
   1. Load station from binary file
   2. Load station from txt file
   3. Print the station
   4. Print the arrested criminals
   5. Add a new cop to the system
   6. Open a new Criminal
   7. Sort cops
   8. Find a cop
   9. Send a cop to a mission!
   10. Send a criminal to an investigation!
   11. Exit
5. To exit the program and free allocated memory, select option 11 from the menu.

## File Structure

- `main.c`: Entry point of the program
- `PoliceManager.h/c`: Core management functionality
- `Cop.h/c`: Cop-related functions and structures
- `Criminal.h/c`: Criminal-related functions and structures
- `Vehicle.h/c`: Vehicle management
- `PrisonCell.h/c`: Prison cell simulation
- `Evidence.h/c`: Evidence handling
- `SystemBin.h/c`: Binary file operations
- `SystemTXTFile.h/c`: Text file operations
- `GeneralFunc.h/c`: Utility functions
- `list.h/c`: Generic linked list implementation
- `Macros.h`: Common macros used across the project

## Data Persistence

The system state can be saved and loaded in both binary and text formats, allowing for data persistence between sessions.

