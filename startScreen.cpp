// Default library
#include <iostream>

// *Menu headers
#include "startScreen.h"
#include "mainMenu.h"

// *Screen utilities
#include "screenUtils.h"

// Gameplay utilities
#include <conio.h>     // For console input/output functions like _getch()
#include <ctime>       // For time-related functions like time() and localtime()
#include <fstream>     // For file operations like reading from and writing to files
#include <string>      // For using the std::string class for string manipulation
#include <windows.h>   // For Windows-specific functions like system() and GetConsoleScreenBufferInfo()
#include <sstream>     // For string stream operations like std::stringstream for converting between strings and other types

using namespace std;

void displayStartScreen() {
    string title = R"(
       _____    ____     ___    ______    ______           __     ___     _   __    ____     ______    ____ 
      / ___/   / __ \   /   |  / ____/   / ____/          / /    /   |   / | / /   / __ \   / ____/   / __ \
      \__ \   / /_/ /  / /| | / /       / __/            / /    / /| |  /  |/ /   / / / /  / __/     / /_/ /
     ___/ /  / ____/  / ___ |/ /___    / /___           / /___ / ___ | / /|  /   / /_/ /  / /___    / _, _/ 
    /____/  /_/      /_/  |_|\____/   /_____/          /_____//_/  |_|/_/ |_/   /_____/  /_____/   /_/ |_|  
                                                                                                    
    )";

    clearScreen();
    
    // Check terminal size
    int terminalWidth = getTerminalWidth();
    int terminalHeight = getTerminalHeight();
    
    // Minimum width and height for the start menu
    const int minWidth = 110;  // Adjust as needed
    const int minHeight = 40; // Adjust as needed
    
    if (terminalWidth < minWidth || terminalHeight < minHeight) {
        clearScreen();
        cout << "Your terminal window is too small to display the game properly." << endl;
        cout << "Please maximize your terminal window and then restart the program." << endl;
        cout << "Press any key to quit the program." << endl;
        
        _getch();  // Wait for any key press
        exit(0);  // Exit the program
    }
    
    clearScreen();
    
    // Calculate vertical padding for centering text vertically
    int verticalPadding = (terminalHeight - 15) / 2; // 7 lines of text including the title and the prompt
    
    // Print vertical padding
    for (int i = 0; i < verticalPadding; i++) {
        cout << endl;
    }
    
    // Print "Hello, Pilot!" and "Welcome to" centered
    printCentered("Hello, Pilot!");
    printCentered("Welcome to ");
    
    // Print the ASCII art centered
    stringstream ss(title);
    string line;
    while (getline(ss, line)) {
        printCentered("\033[1;35m" +line  +"\033[0m");
    }
    
    // Print "Press any key to start!" centered
    printCentered("Press any key to start!");
}