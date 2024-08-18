// Default library
#include <iostream>

// *Menu headers
#include "startScreen.h"
#include "mainMenu.h"
#include "infoMenu.h"
#include "howToPlay.h"
#include "reportIssue.h"

// *Screen utilities
#include "screenUtils.h"

// General utilities
#include <conio.h>   // For console input/output functions like _getch()
#include <ctime>     // For time-related functions like time() and localtime()
#include <string>    // For using the std::string class for string manipulation
#include <sstream>   // For string stream operations like std::stringstream for converting between strings and other types

using namespace std;

void displayInfoMenu() {
    char choice;
    clearScreen();

    // Get terminal size
    int terminalWidth = getTerminalWidth();
    int terminalHeight = getTerminalHeight();

    //Calculate and print vertical padding for centering text vertically
    int verticalPadding = (terminalHeight - 26) / 2; //Adjust as needed
    for (int i = 0; i < verticalPadding; i++) {
        cout << endl;
    }
    
    //Menu ASCII art
    string infoMenuText = R"(
             ,---------------------------,     
             |  /---------------------\  |     
             | | Information           | |     
             | | 1) How to Play        | |     
             | | 2) Report an Issue    | |     
             | | 3) Back to Main Menu  | |     
             | | 4) Go to Start Screen | |     
             | |                       | |     
             | |                       | |     
             |  \_____________________/  |     
             |___________________________|     
                ,---\_____     []     _______/------,     
            /         /______________\           /|    
            /___________________________________ /  | ___ 
             |                                   |   |    ) 
            |  _ _ _                 [-------]  |   |   ( 
            |  o o o                 [-------]  |  /    _)_
            |__________________________________ |/     /  /
        /-------------------------------------/|     ( )/
    /-/1/2/3/4/-/</S/e/l/e/c/t/-/-/-/-/-/-/ /     
  /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     
    )";
    //Print menu centered horizontally
    stringstream ss(infoMenuText);
    string line;
    while (getline(ss, line)) {
        printCentered(line);
    }

    //Menu logic
    choice = _getch();
    switch (choice) {
        case '1':
            displayHowToPlay();
            break;
        case '2':
            reportAnIssue();
            break;
        case '3':
            clearScreen();
            displayMainMenu();
            break;
        case '4':
            clearScreen();
            displayStartScreen();
            _getch();
            clearScreen();
            displayMainMenu();
            break;
        default:
            cout << "Invalid option. Please select a number between 1 and 4." << endl;
            _getch();
            displayInfoMenu();
            break;
    }
}