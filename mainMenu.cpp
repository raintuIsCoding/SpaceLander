// Default library
#include <iostream>

// *Menu headers
#include "mainMenu.h"
#include "startGame.h"
#include "landersCarousel.h"
#include "planetsCarousel.h"
#include "statsMenu.h"
#include "infoMenu.h"

// *Screen utilities
#include "screenUtils.h"

// Gameplay utilities
#include <conio.h>     // For console input/output functions like _getch()
#include <ctime>       // For time-related functions like time() and localtime()
#include <fstream>     // For file operations
#include <string>      // For using the std::string class
#include <windows.h>   // For Windows-specific functions
#include <sstream>     // For string stream operations

string selectedPlanet = "";
string selectedLander = "";

using namespace std;

string green = "\033[1;32m";
string yellow = "\033[1;33m";
string red = "\033[1;31m";
string resetWhite = "\033[0m";

class Lander {
public:
    string name;
    string thrust;
    string fuelLevel;
    string mass;
    string colorThrust;
    string colorFuelLevel;
    string colorMass;

    Lander(string n, string t, string f, string m, string cT, string cF, string cM)
        : name(n), thrust(t), fuelLevel(f), mass(m), colorThrust(cT), colorFuelLevel(cF), colorMass(cM) {}

    void display() const {
        cout << name << ":" << endl;
        cout << colorThrust << "- Thrust: " << thrust << resetWhite << endl;
        cout << colorFuelLevel << "- Fuel Level: " << fuelLevel << resetWhite << endl;
        cout << colorMass << "- Mass: " << mass << resetWhite << endl;
        cout << endl;
    }
};

class Planet {
public:
    string name;
    string gravity;
    string terrain;
    string atmosphere;
    string colorGravity;
    string colorTerrain;
    string colorAtmosphere;

    Planet(string n, string g, string t, string a, string cG, string cT, string cA)
        : name(n), gravity(g), terrain(t), atmosphere(a), colorGravity(cG), colorTerrain(cT), colorAtmosphere(cA) {}

    void display() const {
        cout << name << ":" << endl;
        cout << colorGravity << "- Gravity: " << gravity << resetWhite << endl;
        cout << colorTerrain << "- Terrain: " << terrain << resetWhite << endl;
        cout << colorAtmosphere << "- Atmosphere: " << atmosphere << resetWhite << endl;
        cout << endl;
    }
};


void displayStartGameInfo() {
    clearScreen();

    Lander ranger("Ranger Lander", "400 kN", "40 ML", "150 t.", yellow, yellow, yellow);
    Lander scout("Scout Lander", "220 kN", "20 ML", "100 t.", red, red, green);
    Lander hercules("Hercules Lander", "600 kN", "90 ML", "200 t.", green, green, red);
    Lander rocketX("Rocket X Lander", "", "", "", resetWhite, resetWhite, resetWhite); // Assuming default values for Rocket X

    Planet lithoria("Lithoria Planet", "9.2 m/s^2", "Grassy", "0.8 bar", yellow, yellow, yellow);
    Planet nanow("Nanow Planet", "2.6 m/s^2", "Rocky", "None", green, red, resetWhite);
    Planet jumbotha("Jumbotha Planet", "17.3 m/s^2", "Liquid", "Dense", red, green, resetWhite);
    Planet nebulon("Nebulon Planet", "Variable", "Unknown", "Strange", resetWhite, resetWhite, resetWhite);

    if (selectedLander == "Ranger") {
        ranger.display();
    } else if (selectedLander == "Scout") {
        scout.display();
    } else if (selectedLander == "Hercules") {
        hercules.display();
    } else if (selectedLander == "Rocket_X") {
        rocketX.display();
    }

    if (selectedPlanet == "Lithoria") {
        lithoria.display();
    } else if (selectedPlanet == "Nanow") {
        nanow.display();
    } else if (selectedPlanet == "Jumbotha") {
        jumbotha.display();
    } else if (selectedPlanet == "Nebulon") {
        nebulon.display();
    }

    cout << "Game Controls:" << endl;
    cout << " - 'w' and 's': Full or cut throttle" << endl;
    cout << " - 'd' and 'a': Increase or decrease throttle" << endl;
    cout << " - 'q': Quit the game" << endl;
    cout << endl;
    cout << "Press 'Enter' to begin the game..." << endl;

    while (true) {
        char choice = _getch();
        if (choice == '\r') {  // Enter key
            startGame();
            break;
        }
    }
}


void displayMainMenu() {
    char choice;

    // Get terminal size
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
    
    // Clear the screen
    clearScreen();

    int conditionalPad = 26; //larger number to make it higher, smaller to make it lower

    // Display the selected lander in the upper right corner
    if (!selectedLander.empty()) {
        if (selectedLander == "Ranger"){
            cout << R"(
      ____________
     |Ranger      |
     |     /\     |
     |    (())    |
     |    (  )    |
     |   /||||\   |
     |  [ |/\| ]  |
     |____________|
            )" << endl;
            conditionalPad = 46; //larger number to make it higher, smaller to make it lower
        }
        if (selectedLander == "Scout"){
            cout << R"(
      ____________
     |Scout       | 
     |     /\     |
     |     ||     |
     |     ||     |
     |     ||     |
     |    /||\    |
     |   /:||:\   |
     |   |/||\|   |
     |____________|
            )" << endl;
            conditionalPad = 50; //larger number to make it higher, smaller to make it lower
        }
        if (selectedLander == "Hercules"){
            cout << R"(
      ____________
     |Hercules    |
     |   ____]_   |
     |  | :::: |  |
     |   \ () /   |
     |   |_::_|   |
     |  // VV \\  |
     |____________|
            )" << endl;
            conditionalPad = 46; //larger number to make it higher, smaller to make it lower
        }
        if (selectedLander == "Rocket_X"){
            cout << R"(
      ____________
     |Rocket X    |
     |  _-=/\=-_  |
     |(=_\/..\/_=)|
     | ^-\_AA_/-^ |
     |____________|
            )" << endl;
            conditionalPad = 42; //larger number to make it higher, smaller to make it lower
        }
    }

    // Display the selected planet in the upper right corner (under the lander selection if applicable)
    if (!selectedPlanet.empty()) {
        if (selectedPlanet == "Lithoria"){
            cout << R"(
      ____________
     |Lithoria    |
     |    .--.    |
     |   / #  \   |
     |   \  # /   |
     |    '--'    |
     |____________|
            )" << endl;
            conditionalPad += 17; //larger number to make it higher, smaller to make it lower
        }
        if (selectedPlanet == "Nanow"){
            cout << R"(
      ____________
     |Nanow       | 
     |    .--.    |
     |   / o  \   |
     |   \  . /   |
     |    '--'    |
     |____________|
            )" << endl;
            conditionalPad += 17; //larger number to make it higher, smaller to make it lower
        }
        if (selectedPlanet == "Jumbotha"){
            cout << R"(
      ____________
     |Jumbotha    |
     |    .--.    |
     |   / ~ ~\   |
     |   \~ ~ /   |
     |    '--'    |
     |____________|
            )" << endl;
            conditionalPad += 17; //larger number to make it higher, smaller to make it lower
        }
        if (selectedPlanet == "Nebulon"){
            cout << R"(
      ____________
     |Nebulon     |
     |    .--.    |
     |   /=-~-\   |
     |   \=-=-/   |
     |    '--'    |
     |____________|
            )" << endl;
            conditionalPad += 17; //larger number to make it higher, smaller to make it lower
        }
    }

    // Calculate vertical padding for centering text vertically
    int verticalPadding = (terminalHeight - conditionalPad) / 2; // 18 lines of text including the title and the prompt

    // Print vertical padding
    for (int i = 0; i < verticalPadding; i++) {
        cout << endl;
    }
    
    // Print the menu options in the top left corner
    string mainMenuText = R"(
             ,---------------------------,     
             |  /---------------------\  |     
             | | Main Menu             | |     
             | | 1) Start Game         | |     
             | | 2) Landers            | |     
             | | 3) Planets            | |     
             | | 4) Stats              | |     
             | | 5) Info               | |     
             | | 6) Quit               | |     
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
    /-/1/2/3/4/5/6/-/</S/e/l/e/c/t/-/-/-/-/ /     
  /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ /     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     
    )";
    // Print the ASCII art centered
    stringstream ss(mainMenuText);
    string line;
    while (getline(ss, line)) {
        printCentered(line);
    }

    choice = _getch();  // Use _getch() to get a single character input without Enter
    
    if (choice == '1') {
        if (selectedLander.empty() || selectedPlanet.empty()) {
            clearScreen();
            cout << R"(
        _..._                 Hey there pilot! My name is Astro!
      .'     '.      _        Looks like you might be getting ahead of yourself a little bit!
     /    .-""-\   _/ \       To survive your decent, you need to select lander! Otherwise you'll totally be falling all on your own...
   .-|   /:.   |  |   |       Oh, and pick your poison *ehem* I mean planet, and be careful not to choose anything too crazy!
   |  \  |:.   /.-'-./        Hit any key to return to the main menu and make your selections!
   | .-'-;:__.'    =/
   .'=  *=|ASTRO_.='
  /   _.  |    ;
 ;-.-'|    \   |
/   | \    _\  _\
\__/'._;.  ==' ==\
         \    \   |
         /    /   /
         /-._/-._/
         \   `\  \
          `-._/._/
            )";
            _getch();  // Wait for any key press
            displayMainMenu();  // Redisplay the main menu
        } else {
            displayStartGameInfo();
        }
    } else if (choice == '2') {
        displayLandersCarousel();
    } else if (choice == '3') {
        displayPlanetsCarousel();
    } else if (choice == '4') {
        displayStatsMenu();
    } else if (choice == '5') {
        displayInfoMenu();
    } else if (choice == '6') {
        clearScreen();
        // Calculate vertical padding for centering text vertically
        int verticalPadding = (terminalHeight - 6) / 2; //terminalHeight - larger number to make it higher, smaller to make it lower

        // Print vertical padding
        for (int i = 0; i < verticalPadding; i++) {
            cout << endl;
        }

        printCentered("Exiting the program...");
        exit(0);  // Exit the program
    } else {
        cout << "Invalid option. Please select a number between 1 and 6." << endl;
        _getch();  // Wait for any key press to continue
        displayMainMenu();  // Redisplay the main menu
    }
}