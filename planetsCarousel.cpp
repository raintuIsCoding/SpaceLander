//Default library
#include <iostream>
#include <string> //For using the std::string class for string manipulation
#include <vector>
#include <map>

//*Menu headers
#include "mainMenu.h"
#include "planetsCarousel.h"

//*Screen utilities
#include "screenUtils.h"

//Gameplay utilities
#include <conio.h>      //For console input/output functions like _getch()
#include <ctime>        //For time-related functions like time() and localtime()
#include <fstream>      //For file operations like reading from and writing to files
#include <sstream>      //For string stream operations like std::stringstream for converting between strings and other types
#include <filesystem>   //For filesystem operations (C++17 or later)
#include <windows.h>    //For Windows-specific functions like system() and GetConsoleScreenBufferInfo()

using namespace std;

//Define ASCII art for each planet
const map<string, string> planetArtMap = {
    {"Lithoria", R"(
___________________________
| Lithoria                  |
|                           |
____________        |          .-##"-.          |        ____________
| ???        |       |        .`###### `.        |       | Nanow      |
|            |       |       /   ####    \       |       |            |
|            |       |       ;     ##    ;       |       |            |
|   ??????   |       |       \      #    /       |       |    .--.    |
|  ????????  |       |        '.  #### .'        |       |   / o  \   |
|  ????????  |       |          '--##-'          |       |   \  . /   |
|   ??????   |       |                           |       |    '--'    |
|            |       |                           |       |            |
|            |       |  Gravity: 9.2 m/s^2       |       |            |
|            |       |  Air density: 1.3 kg/m^3  |       |            |
|____________|       |  Surface: Grassy meadow   |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
    {"Nanow", R"(
___________________________
| Nanow                     |
|                           |
____________        |          .-"""-.          |        ____________
| Lithoria   |       |        .`       `.        |       | Jumbotha   |
|            |       |       /  ( )    . \       |       |            |
|            |       |       ;           ;       |       |            |
|    .--.    |       |       \ .    o    /       |       |    .--.    |
|   / #  \   |       |        '.       .'        |       |   / ~ ~\   |
|   \  # /   |       |          '-----'          |       |   \~ ~ /   |
|    '--'    |       |                           |       |    '--'    |
|            |       |                           |       |            |
|            |       |  Gravity: 2.6 m/s^2       |       |            |
|            |       |  Air density: 0 kg/m^3    |       |            |
|____________|       |  Surface: Rocky           |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
    {"Jumbotha", R"(
___________________________
| Jumbotha                  |
|                           |
____________        |          .-"""-.          |        ____________
| Nanow      |       |        .`~   ~ ~`.        |       | ???        |
|            |       |       /   ~   ` ~ \       |       |            |
|            |       |       ; ~     ~   ;       |       |            |
|    .--.    |       |       \   `~      /       |       |   ??????   |
|   / o  \   |       |        '. ~   `~.'        |       |  ????????  |
|   \  . /   |       |          '-----'          |       |  ????????  |
|    '--'    |       |                           |       |   ??????   |
|            |       |                           |       |            |
|            |       |  Gravity: 17.3 m/s^2      |       |            |
|            |       |  Air density: 3.8 kg/m^3  |       |            |
|____________|       |  Surface: H2O             |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
    {"Nebulon", R"(
___________________________
| Nebulon                   |
|                           |
____________        |          .-"""-.          |        ____________
| Jumbotha   |       |        .` - ====`.        |       | Lithonia   |
|            |       |       / -=--=-~=--\       |       |            |
|            |       |       ; -=-=~=-===;       |       |            |
|    .--.    |       |       \ -=-~~=--@ /       |       |    .--.    |
|   / ~ ~\   |       |        '. ~ -=`~.'        |       |   / #  \   |
|   \~ ~ /   |       |          '-----'          |       |   \  # /   |
|    '--'    |       |                           |       |    '--'    |
|            |       |                           |       |            |
|            |       |  Gravity: ??? m/s^2       |       |            |
|            |       |  Air density: ??? kg/m^3  |       |            |
|____________|       |  Surface: N/A             |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
};

void displayPlanetsCarousel() {
    int currentPlanet = 0;  // Index of the currently displayed planet
    char choice;
    vector<string> planets = {"Lithoria", "Nanow", "Jumbotha", "Nebulon"};  // List of planets

    while (true) {
        clearScreen();

        // Check terminal size
        int terminalWidth = getTerminalWidth();
        int terminalHeight = getTerminalHeight();

        // Calculate vertical padding for centering text vertically
        int verticalPadding = (terminalHeight - 22) / 2; // 22 lines of text including the title and the prompt

        // Print vertical padding
        for (int i = 0; i < verticalPadding; i++) {
            cout << endl;
        }

        // Display the current planet page
        displayPlanetsPage(planets[currentPlanet]);

        // Read user input
        choice = _getch();
        if (choice == 75) {  // Left arrow key
            currentPlanet = (currentPlanet - 1 + planets.size()) % planets.size();
        } else if (choice == 77) {  // Right arrow key
            currentPlanet = (currentPlanet + 1) % planets.size();
        } else if (choice == '\r') {  // Enter key
            confirmPlanetSelection(planets[currentPlanet]);  // Function to handle the selected planet
            break;
        } else if (choice == 'q') {  // 'q' key to go back to the main menu
            clearScreen();
            displayMainMenu();
            break;
        }
    }
}

void displayPlanetsPage(const string& planetName) {
    // Centered text for the planet name
    printCentered("Choose your Planet:");

    // Retrieve and display the ASCII art for the current planet
    auto it = planetArtMap.find(planetName);
    if (it != planetArtMap.end()) {
        stringstream ss(it->second);
        string line;
        while (getline(ss, line)) {
            printCentered(line);
        }
    } else {
        printCentered("No ASCII art available for this planet.");
    }
}

void confirmPlanetSelection(const string& planetName) {
    clearScreen();

    srand(time(0));

    // Update the global selectedLander variable
    selectedPlanet = planetName;
    if (selectedPlanet == "Lithoria"){
        gravity = 9.2;
    } else if (selectedPlanet == "Nanow"){
        gravity = 2.6;
    } else if (selectedPlanet == "Jumbotha"){
        gravity = 17.3;
    } else if (selectedPlanet == "Nebulon"){
        gravity = rand()%25;
    }
    // Velocity threshold for a successful landing
    selectedPlanet = planetName;
    if (selectedPlanet == "Lithoria"){
        maxSurfaceLandingV = -10.0;
    } else if (selectedPlanet == "Nanow"){
        maxSurfaceLandingV = -5.0;
    } else if (selectedPlanet == "Jumbotha"){
        maxSurfaceLandingV = -15.0;
    } else if (selectedPlanet == "Nebulon"){
        maxSurfaceLandingV = rand()%20;
    }

    // Check terminal size
    int terminalWidth = getTerminalWidth();
    int terminalHeight = getTerminalHeight();

    // Calculate vertical padding for centering text vertically
    int verticalPadding = (terminalHeight - 12) / 2; // 18 lines of text including the title and the prompt

    // Print vertical padding
    for (int i = 0; i < verticalPadding; i++) {
        cout << endl;
    }
    printCentered("You have selected " + planetName + " as your planet.");
    printCentered(" ");
    printCentered("Press any key to return to the main menu...");
    _getch();
    displayMainMenu();
}