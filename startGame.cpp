//Default library
#include <iostream>

//*Menu headers
#include "mainMenu.h"
#include "startGame.h"
#include "landersCarousel.h"
#include "planetsCarousel.h"
#include "statsMenu.h"

//*Screen utilities
#include "screenUtils.h"

// Gameplay utilities
#include <conio.h>      // For console input/output functions like _getch()
#include <ctime>        // For time-related functions like time() and localtime()
#include <fstream>      // For file operations like reading from and writing to files
#include <string>       // For using the std::string class for string manipulation
#include <windows.h>    // For Windows-specific functions like system() and GetConsoleScreenBufferInfo()
#include <WinUser.h>    // For Windows-specific user interface functions (part of the Windows API)
#include <sstream>      // For string stream operations like std::stringstream for converting between strings and other types
#include <chrono>       // For timekeeping and duration utilities
#include <thread>       // For managing threads and thread sleep functions
#include <iomanip>      // For manipulating input/output formatting
#include <vector>       // For using the std::vector container

using namespace std;
using namespace chrono;

double maxSurfaceLandingV = 0.0;
double gravity = 0.0;
double thrust = 0.0;
double THRUST_FORCE = 0.0;
float fuelLevel;           // Initial fuel level
float fuelConsume = 0.0f;  // Initial fuel consumption rate
string playerName = loadPlayerName(); // Load player's name from file

// Function prototypes
void handleInput(bool& isRunning, float& thrust, bool& fullThrust, bool& cutEngines, bool& quit, float position, float& fuelLevel, float& fuelConsume);
void updateGameState(bool& isRunning, float& position, float& velocity, float& previousVelocity, float& remainingFuel, float thrust, bool fullThrust, 
                     bool cutEngines, float deltaTime, int& landerY, float& fuelLevel, float fuelConsume);
void renderGame(float position, float velocity, float thrust, int landerY, bool isLanded, bool isOutOfFrame, float finalVelocity, float fuelLevel);
void clearScreen();
void displayMainMenu();
void displayLandingResult(float finalVelocity, float remainingFuel, int finalScore);
void flushInputBuffer();
void renderLander(int centerX, int landerY, vector<string>& screen, float);
int calculateScore(float fuelLevel, float previousVelocity);

// Global variable to hold the selected lander type
int selectedLanderIndex = 0; // Index for the selected lander, modify this as needed

void startGame() {
    bool isRunning = true;
    bool fullThrust = false;
    bool cutEngines = false;
    bool quit = false;
    float position = 100.0f;       // Initial position (altitude) reduced to 100 meters
    float velocity = 0.0f;         // Initial velocity
    float previousVelocity = 0.0f; // Velocity of the previous frame
    float remainingFuel = 0.0f;
    float thrust = 0.0f;           // Initial thrust
    int landerY = 3;               // Initial Y position of the lander
    bool isLanded = false;         // Flag to indicate if the lander has landed
    bool isOutOfFrame = false;     // Flag to indicate if the lander is out of frame
    float fuelLevel;
    float fuelConsume = 0.0f;

    // Create stats folder
    createStatsDirectory();

    // Reset fuel level based on selected lander
    fuelLevel = getInitialFuelLevel(selectedLander);
    fuelConsume = 0.0f; // Reset fuel consumption rate

    auto lastTime = steady_clock::now();

    // Load player's name from file
    static string playerName = loadPlayerName();

    while (isRunning) {
        auto currentTime = steady_clock::now();
        duration<float> deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        handleInput(isRunning, thrust, fullThrust, cutEngines, quit, position, fuelLevel, fuelConsume);
        updateGameState(isRunning, position, velocity, previousVelocity, remainingFuel, thrust, fullThrust, cutEngines, deltaTime.count(), landerY, fuelLevel, fuelConsume);
        isLanded = (position <= 0.0f); // Update the landed state flag
        isOutOfFrame = (position >= 101.0f);
        renderGame(position, velocity, thrust, landerY, isLanded, isOutOfFrame, previousVelocity, fuelLevel);

        this_thread::sleep_for(milliseconds(16)); // Cap frame rate at ~60 FPS

        if (isOutOfFrame) {
            // Handle case where lander goes too high
            isRunning = false;
            cout << "The lander has gone too high and is out of frame. Resetting the game..." << endl;
            this_thread::sleep_for(seconds(2)); // Freeze the game screen for 2 seconds
            clearScreen();
            displayStartGameInfo();
            return; // Exit the function to reset the game
        }

    }

    // Freeze the game screen for 2 seconds
    flushInputBuffer();
    this_thread::sleep_for(seconds(2));

    // Calculate final score
    float finalScore = calculateScore(fuelLevel, previousVelocity);

    if (quit) {
        finalScore = 0; // Set score to 0 if the player quits
    } else if (position <= 0.0f) {
        if (abs(previousVelocity) <= abs(maxSurfaceLandingV)) {
            finalScore = calculateScore(fuelLevel, previousVelocity);
        } else {
            finalScore = 0; // Set score to 0 if the player crashes
        }
    }

    // Display landing result with final score
    displayLandingResult(previousVelocity, remainingFuel, finalScore);
}

void handleInput(bool& isRunning, float& thrust, bool& fullThrust, bool& cutEngines, bool& quit, float position, float& fuelLevel, float& fuelConsume) {
    if (_kbhit() && position > 0.0f) { // Only allow input if above ground level
        char charInput = _getch();
        // "toLower"
        switch (charInput) {
            case 'w':
            case 'W':
                if (fuelLevel > 0.0f){
                    fullThrust = true;
                }
                break;
            case 's':
            case 'S':
                if (fuelLevel > 0.0f){
                    cutEngines = true;
                }
                break;
            case 'd': // Throttle up key (Increase thrust)
            case 'D':
                if (fuelLevel > 0.0f){
                    thrust += 0.5f;
                }
                break;
            case 'a': // Throttle down key (Decrease thrust)
            case 'A':
                if (fuelLevel > 0.0f){
                    thrust -= 0.5f;
                }
                if (thrust < 0.0f) thrust = 0.0f; // Ensure thrust doesn't go below 0
                break;
            case 'q':
                quit = true;
                isRunning = false;
                break;
        }
    }
    if (fullThrust) {
        // if (fuelLevel >= THRUST_FORCE) {
            thrust = THRUST_FORCE;
        // }
        fullThrust = false; // Reset after applying thrust
    }
    if (cutEngines) {
        thrust = 0.0f;
        cutEngines = false; // Reset after cutting engines
    }

    // Update fuel consumption rate based on thrust
    fuelConsume = thrust * 0.25f; // Adjust the fuel consumption rate as necessary
}

void updateGameState(bool& isRunning, float& position, float& velocity, float& previousVelocity, float& remainingFuel, float thrust, 
                     bool fullThrust, bool cutEngines, float deltaTime, int& landerY, float& fuelLevel, float fuelConsume) {
    // Store current velocity before updating it
    previousVelocity = velocity;

    // Store remaining fuel levels
    remainingFuel = fuelLevel;

    // Update velocity and position based on thrust and gravity
    velocity += (thrust - gravity) * deltaTime;
    position += velocity * deltaTime;

    // Clamp position to ground level
    if (position <= 0.0f) {
        position = 0.0f;
        velocity = 0.0f;
        isRunning = false; // Stop the game loop when the lander reaches the ground
    }

    // Map the position (altitude) to the screen's Y coordinate
    int maxY = 32 - 3; // The maximum Y position for the lander to stay within the screen
    landerY = maxY - static_cast<int>((position / 100.0f) * maxY);

    // Update fuel level based on consumption rate
    fuelLevel -= fuelConsume * deltaTime;
    if (fuelLevel <= 0.01) {
        fuelLevel = 0.0f;
        thrust = 0.0f; // Cut thrust if out of fuel
    }
}

void renderLander(int centerX, int landerY, vector<string>& screen, float thrust) {
    if (thrust > 0){
        // Add the lander to the grid at the specified Y position
        screen[landerY][centerX] = '[';
        screen[landerY][centerX + 1] = ']';
        screen[landerY + 1][centerX] = '/';
        screen[landerY + 1][centerX + 1] = '\\';
        screen[landerY + 2][centerX] = '*';
        screen[landerY + 2][centerX + 1] = '*';
    } else {
        // Add the lander to the grid at the specified Y position
        screen[landerY][centerX] = '[';
        screen[landerY][centerX + 1] = ']';
        screen[landerY + 1][centerX] = '/';
        screen[landerY + 1][centerX + 1] = '\\';
    }
    // MINI LANDER ART:
    //
    //     []          []          []          []          []
    //     /\          /\          /\          /\          /\ 
    //                 **          ^^          ##          !!
    //
}

void renderGame(float position, float velocity, float thrust, int landerY, bool isLanded, bool isOutOfFrame, float finalVelocity, float fuelLevel) {
    clearScreen();

    // Draw the top border of the game screen
    cout << " ________________________________________" << endl;

    // Create a 2D grid representing the game screen
    vector<string> screen(32, string(38, ' '));

    // Draw the lander or the landed state
    int centerX = 18; // Center X coordinate for the lander
    if (!isLanded || !isOutOfFrame) {
        renderLander(centerX, landerY, screen, thrust);
    } else {
        screen[landerY][centerX] = '[';
        screen[landerY][centerX + 1] = ']';
        screen[landerY + 1][centerX] = '/';
        screen[landerY + 1][centerX + 1] = '\\';
    }

    // Render the grid to the console
    for (int i = 0; i < screen.size(); ++i) {
        cout << "| " << screen[i] << " |" << endl;
    }

    // Draw the surface or landed state visuals
    if (!isLanded) {
        if (selectedPlanet == "Jumbotha"){
            cout << "|               ,~^~~~.~~,               |" << endl;
        } else if (selectedPlanet == "Lithoria" || selectedPlanet == "Nanow" || selectedPlanet == "Nebulon"){
            cout << "|               __________               |" << endl;
        }
        // Custom surface for each planet
        if (selectedPlanet == "Lithoria") {
            cout << "|1---===^^****`` ## # ### ``****^^===----|" << endl;
            cout << "| # ## # ### ## # #### # # ## # ### # ## |" << endl;
        } else if (selectedPlanet == "Nanow") {
            cout << "|2---===^^****``        ^ ``****^^===----|" << endl;
            cout << "|    (___)    ^  O :           .*    ;   |" << endl;
        } else if (selectedPlanet == "Jumbotha") {
            cout << "|3---===^^****`` ~^~~-=^-~``****^^===----|" << endl;
            cout << "|=^~~~~=-,~^~~-~~~,,~~~~^~~~,~~~^~~,~~~ ~|" << endl;
        } else if (selectedPlanet == "Nebulon") {
            cout << "|4---===^^****``&!(#  %#@!``****^^===----|" << endl;
            cout << "|& % $( *@# ^ %$ ()$#&^  $^@ *(@!^ * &^% |" << endl;
        }

        // Draw the status line with game data
        cout << "|----------------------------------------|" << endl;
        cout << "| Altitude: " << setw(14) << fixed << setprecision(1) << position << " meters        |" << endl;
        cout << "| Velocity: " << setw(14) << fixed << setprecision(1) << velocity << " m/s           |" << endl;
        cout << "| Thrust: " << setw(16) << thrust << " N             |" << endl; // Live update of thrust
        cout << "| Fuel: " << setw(18) << fuelLevel << " ML            |" << endl; // Live update of fuel
        // Custom surface for each planet
        if (selectedPlanet == "Lithoria") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << maxSurfaceLandingV << " m/s (grassy) |" << endl;
        } else if (selectedPlanet == "Nanow") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << maxSurfaceLandingV << " m/s   (rocky) |" << endl;
        } else if (selectedPlanet == "Jumbotha") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << maxSurfaceLandingV << " m/s (splashy)|" << endl;
        } else if (selectedPlanet == "Nebulon") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << -maxSurfaceLandingV << " m/s      (?) |" << endl;
        }
        // Draw the bottom border of the game screen
        cout << "|________________________________________|" << endl;

        // Draw the game controls
        cout << " Controls: W - Full Thrust, S - Cut Engines, D - Throttle Up, A - Throttle Down, Q - Quit" << endl;

        // Add some space at the bottom for clarity
        cout << R"(
            )" << endl;
    } else {

        clearScreen();

        cout << " ________________________________________" << endl;

        // Render the grid to the console
        for (int i = 0; i < screen.size()-3; ++i) {
            cout << "| " << screen[i] << " |" << endl;
        }

        // cout << velocity << endl;
        // cout << maxSurfaceLandingV << endl;
        if (finalVelocity < maxSurfaceLandingV){
            cout << "|                 _~**~_                 |" << endl;
            cout << "|               (%{_&`}_~)               |" << endl;
            cout << "|                   ||                   |" << endl;
            cout << "|               ___(~*)___               |" << endl;
        } else {
            cout << "|                                        |" << endl;
            cout << "|                                        |" << endl;
            cout << "|                   []                   |" << endl;
            cout << "|               ____/\\____               |" << endl;
        }

        // Custom surface for each planet
        if (selectedPlanet == "Lithoria") {
            cout << "|----===^^****`` ## # ### ``****^^===----|" << endl;
            cout << "| # ## # ### ## # #### # # ## # ### # ## |" << endl;
        } else if (selectedPlanet == "Nanow") {
            cout << "|----===^^****``        ^ ``****^^===----|" << endl;
            cout << "|    (___)    ^  O :           .*    ;   |" << endl;
        } else if (selectedPlanet == "Jumbotha") {
            cout << "|----===^^****`` ~^~~-=^-~``****^^===----|" << endl;
            cout << "|=^~~~~=-,~^~~-~~~,,~~~~^~~~,~~~^~~,~~~ ~|" << endl;
        } else if (selectedPlanet == "Nebulon") {
            cout << "|----===^^****``&!(#  %#@!``****^^===----|" << endl;
            cout << "|& % $( *@# ^ %$ ()$#&^  $^@ *(@!^ * &^% |" << endl;
        }

        // Draw the status line with game data
        cout << "|----------------------------------------|" << endl;
        cout << "| Altitude: " << setw(14) << fixed << setprecision(1) << position << " meters        |" << endl;
        cout << "| Velocity: " << setw(14) << fixed << setprecision(2) << abs(finalVelocity) << " m/s           |" << endl;
        cout << "| Thrust: " << setw(16) << thrust << " N             |" << endl; // Live update of thrust
        cout << "| Fuel: " << setw(18) << fixed << setprecision(2) << abs(fuelLevel) << " ML            |" << endl; // Live update of fuel
        // Custom surface for each planet
        if (selectedPlanet == "Lithoria") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << maxSurfaceLandingV << " m/s (grassy) |" << endl;
        } else if (selectedPlanet == "Nanow") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << maxSurfaceLandingV << " m/s   (rocky) |" << endl;
        } else if (selectedPlanet == "Jumbotha") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << maxSurfaceLandingV << " m/s (splashy)|" << endl;
        } else if (selectedPlanet == "Nebulon") {
            cout << "| Gravity: " << setw(15) << fixed << setprecision(1) << gravity << " m/s           |" << endl;
            cout << "| Safe landing speed: " << setw(4) << fixed << setprecision(1) << maxSurfaceLandingV << " m/s       (?) |" << endl;
        }
        // Draw the bottom border of the game screen
        cout << "|________________________________________|" << endl;

        // Draw the game controls
        cout << " Controls: W - Full Thrust, S - Cut Engines, D - Throttle Up, A - Throttle Down, Q - Quit" << endl;
        cout << endl;
    }
}

int calculateScore(float remainingFuel, float finalVelocity) {
    // Score based on remaining fuel and final velocity
    const float fuelWeight = 5.0f;   // Weight for fuel (adjust as needed)
    const float velocityWeight = 10.0f; // Weight for velocity (adjust as needed)
    
    // Ensure finalVelocity is non-negative to avoid negative scores
    finalVelocity = abs(finalVelocity);

    remainingFuel = abs(remainingFuel);

    // Calculate score
    int score = static_cast<int>(remainingFuel * fuelWeight - finalVelocity * velocityWeight);
    return max(score, 0); // Ensure score is non-negative
}

void displayLandingResult(float finalVelocity, float remainingFuel, int finalScore) {
    bool resultsDisplayed = false;
    
    while (!resultsDisplayed) {
        clearScreen();

        // Check win/loss condition based on velocity
        if (abs(finalVelocity) <= abs(maxSurfaceLandingV)) {
            cout << " Congratulations Pilot! You have successfully landed!" << endl;
            cout << endl;
        } else {
            cout << " You crashed... Try again!" << endl;
            cout << endl;
        }

        // Display final velocity rounded to 2 decimal places
        cout << fixed << setprecision(2); // Set the precision to 2 decimal places
        cout << " Final velocity: " << finalVelocity << " m/s" << endl;
        cout << endl;
        cout << fixed << setprecision(2); // Set the precision to 2 decimal places
        cout << " Remaining fuel: " << remainingFuel << " ML" << endl;
        cout << endl;

        // Display final score
        cout << " Final score: " << finalScore << " points" << endl;
        // printCentered("Final score: " + finalScore + " points");
        cout << endl;

        cout << R"(
        _..._                 Great attempt Pilot!
      .'     '.      _        If you'd like any tips or a tutorial on how to play, check out the info tab at the Main Menu!
     /    .-""-\   _/ \       Also, if you'd like to check out the highscores, look for the Stats page!
   .-|   /:.   |  |   |       
   |  \  |:.   /.-'-./        
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
            )" << endl;

        // Ignore input for half a second
        this_thread::sleep_for(milliseconds(500)); // Wait for half a second

        // Clear the input buffer
        flushInputBuffer();

        // Prompt for player's name after the game ends and immediately record the score
        string playerName = promptForPlayerName();
        savePlayerName(playerName);
        recordScore(playerName, finalScore, finalVelocity, remainingFuel);
        updateStats(playerName, finalScore, finalVelocity, remainingFuel);

        cout << " Press 'r' to retry, 'n' to update your name for the scoreboard, or press any other key to return to the Main Menu." << endl;
        cout << endl;
        char resultsCharChoice = _getch();
        if (resultsCharChoice == 'n' || resultsCharChoice == 'N') {
            displayAskName();
            cout << endl;
            cout << " Your name has been successfully recorded!" << endl;
            cout << endl;
            cout << " To view your scores, navigate to the Stats Screen from the Main Menu." << endl;
            cout << endl;
            cout << " Press 'r' to try landing again, 'n' to update your name for the scoreboard, or press any other key to return to the Main Menu." << endl;
            cout << endl;
            resultsCharChoice = _getch();
            if (resultsCharChoice == 'r' || resultsCharChoice == 'R') {
                clearScreen();
                startGame();
                resultsDisplayed = true;
            } else if (resultsCharChoice == 'n' || resultsCharChoice == 'N') {
                displayAskName();
            } else {
                clearScreen();
                displayMainMenu();
                resultsDisplayed = true;
            }
        } else if (resultsCharChoice == 'r' || resultsCharChoice == 'R'){
                clearScreen();
                startGame();
        } else {
                clearScreen();
                displayMainMenu(); // Assuming this function is already defined
        }
    }
}