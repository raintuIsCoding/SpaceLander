// Default library
#include <iostream>

// *Menu headers
#include "startScreen.h"
#include "mainMenu.h"
#include "startGame.h"
#include "landersCarousel.h"
#include "planetsCarousel.h"
#include "statsMenu.h"
#include "infoMenu.h"
#include "howToPlay.h"
#include "reportIssue.h"

// *Screen utilities
#include "screenUtils.h"

// Gameplay utilities
#include <conio.h>     // For console input/output functions like _getch()
#include <ctime>       // For time-related functions like time() and localtime()
#include <fstream>     // For file operations like reading from and writing to files
#include <string>      // For using the std::string class for string manipulation
#include <windows.h>   // For Windows-specific functions like system() and GetConsoleScreenBufferInfo()
#include <sstream>     // For string stream operations like std::stringstream for converting between strings and other types

// Function to clear the screen
void clearScreen() {
    // Windows-specific clear screen command
    system("CLS");
}

//Function to clear any current stored input
void flushInputBuffer() {
    while (_kbhit()) {
        _getch();
    }
}

// Function to get the width of the terminal window
int getTerminalWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.X;
}

// Function to get the height of the terminal window
int getTerminalHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Return the number of visible lines in the terminal
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Function to print text centered
void printCentered(const string& text) {
    int terminalWidth = getTerminalWidth();
    int padding = (terminalWidth - text.length()) / 2;
    for (int i = 0; i < padding; i++) {
        cout << ' ';
    }
    cout << text << endl;
}
