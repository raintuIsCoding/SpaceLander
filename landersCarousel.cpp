//Default library
#include <iostream>

//*Menu headers
#include "mainMenu.h"
#include "startGame.h"
#include "landersCarousel.h"

//*Screen utilities
#include "screenUtils.h"

// Gameplay utilities
#include <conio.h>    // For console input/output functions like _getch()
#include <ctime>      // For time-related functions like time() and localtime()
#include <fstream>    // For file operations like reading from and writing to files
#include <sstream>    // For string stream operations like std::stringstream for converting between strings and other types
#include <string>     // For using the std::string class for string manipulation
#include <vector>     // For using the std::vector container
#include <map>        // For using the std::map container

using namespace std;

// Define ASCII art for each lander
const map<string, string> landerArtMap = {
    {"Ranger", R"(
___________________________
| Ranger                    |
|                           |
____________        |                           |        ____________
| ???        |       |            /\             |       | Scout      |
|            |       |           (())            |       |            |
|            |       |           (  )            |       |     /\     |
|            |       |          /||||\           |       |     ||     |
|   ??????   |       |         [ |/\| ]          |       |     ||     |
| ?????????? |       |                           |       |     ||     |
|   ??????   |       |                           |       |    /||\    |
|            |       |                           |       |   /:||:\   |
|            |       |  Thrust: 400 kN           |       |   |/||\|   |
|            |       |  Fuel: 40 ML              |       |            |
|____________|       |  Mass: 150 t.             |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
    {"Scout", R"(
___________________________
| Scout                     |
|                           |
____________        |            /\             |        ____________
| Ranger     |       |            ||             |       | Hercules   |
|            |       |            ||             |       |            |
|            |       |            ||             |       |            |
|     /\     |       |           /||\            |       |   ____]_   |
|    (())    |       |          /:||:\           |       |  | :::: |  |
|    (  )    |       |          |/||\|           |       |   \ () /   |
|   /||||\   |       |                           |       |   |_::_|   |
|  [ |/\| ]  |       |                           |       |  // VV \\  |
|            |       |  Thrust: 220 kN           |       |            |
|            |       |  Fuel: 20 ML              |       |            |
|____________|       |  Mass: 100 t.             |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
    {"Hercules", R"(
___________________________
| Hercules                  |
|                           |
____________        |                           |        ____________
| Scout      |       |          ____]_           |       | ???        |
|            |       |         | :::: |          |       |            |
|     /\     |       |          \ () /           |       |            |
|     ||     |       |          |_::_|           |       |            |
|     ||     |       |         // VV \\          |       |   ??????   |
|     ||     |       |                           |       | ?????????? |
|    /||\    |       |                           |       |   ??????   |
|   /:||:\   |       |                           |       |            |
|   |/||\|   |       |  Thrust: 600 kN           |       |            |
|            |       |  Fuel: 80 ML              |       |            |
|____________|       |  Mass: 200 t.             |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
    {"Rocket_X", R"(
___________________________
| Rocket X                  |
|                           |
____________        |                           |        ____________
| Hercules   |       |                           |       | Ranger     |
|            |       |          //--\\           |       |            |
|            |       |      __--======--__       |       |            |
|   ____]_   |       |   (=__\  /....\  /__=)    |       |     /\     |
|  | :::: |  |       |       ^-\__AA__/-^        |       |    (())    |
|   \ () /   |       |                           |       |    (  )    |
|   |_::_|   |       |                           |       |   /||||\   |
|  // VV \\  |       |                           |       |  [ |/\| ]  |
|            |       |  Thrust: ??? kN           |       |            |
|            |       |  Fuel: ??  ML             |       |            |
|____________|       |  Mass: ??? t.             |       |____________|
|  -----------------------  |
|  Press Enter to select    |
|  Press 'q' to cancel      |
|  Left/Right to navigate   |
|___________________________|
)"},
};

void displayLandersCarousel() {
    int currentLander = 0;  // Index of the currently displayed lander
    char choice;
    vector<string> landers = {"Ranger", "Scout", "Hercules", "Rocket_X"};  // List of landers

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

        // Display the current lander page
        displayLandersPage(landers[currentLander]);

        // Read user input
        choice = _getch();
        if (choice == 75) {  // Left arrow key
            currentLander = (currentLander - 1 + landers.size()) % landers.size();
        } else if (choice == 77) {  // Right arrow key
            currentLander = (currentLander + 1) % landers.size();
        } else if (choice == '\r') {  // Enter key
            confirmLandersSelection(landers[currentLander]);  // Function to handle the selected lander
            break;
        } else if (choice == 'q') {  // 'q' key to go back to the main menu
            clearScreen();
            displayMainMenu();
            break;
        }
    }
}

void displayLandersPage(const string& landerName) {
    // Centered text for the lander name
    printCentered("Choose your SPACE LANDER:");

    // Retrieve and display the ASCII art for the current lander
    auto it = landerArtMap.find(landerName);
    if (it != landerArtMap.end()) {
        stringstream ss(it->second);
        string line;
        while (getline(ss, line)) {
            printCentered(line);
        }
    } else {
        printCentered("No ASCII art available for this lander.");
    }
}

// Function to get the initial fuel level based on the selected lander
float getInitialFuelLevel(const string& landerName) {
    if (landerName == "Ranger") {
        return 40.0f;
    } else if (landerName == "Scout") {
        return 20.0f;
    } else if (landerName == "Hercules") {
        return 90.0f;
    } else if (landerName == "Rocket_X") {
        return static_cast<float>(rand() % 150);
    }
    return 0.0f; // Default fuel level if lander is not found
}

void confirmLandersSelection(const string& landerName) {
    clearScreen();

    // Update the global selectedLander variable
    selectedLander = landerName;
    if (selectedLander == "Ranger"){
        THRUST_FORCE = (400/150)*10;
    } else if (selectedLander == "Scout"){
        THRUST_FORCE = (220/100)*10;
    } else if (selectedLander == "Hercules"){
        THRUST_FORCE = (600/200)*10;
    } else if (selectedLander == "Rocket_X"){
        THRUST_FORCE = rand()%25;
    }

    // Update the global selectedLander variable
    selectedLander = landerName;

    // Check terminal size
    int terminalWidth = getTerminalWidth();
    int terminalHeight = getTerminalHeight();

    // Calculate vertical padding for centering text vertically
    int verticalPadding = (terminalHeight - 12) / 2; // 18 lines of text including the title and the prompt

    // Print vertical padding
    for (int i = 0; i < verticalPadding; i++) {
        cout << endl;
    }
    printCentered("You have selected " + landerName + " as your lander.");
    printCentered(" ");
    printCentered("Press any key to return to the main menu...");
    _getch();
    displayMainMenu();
}