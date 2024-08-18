// Default library
#include <iostream>

// *Menu headers
#include "mainMenu.h"
#include "infoMenu.h"
#include "howToPlay.h"

// *Screen utilities
#include "screenUtils.h"

// Input utilities
#include <conio.h> // For console input/output functions like _getch()


using namespace std;

void displayHowToPlay() {
    clearScreen();
    cout << "HOW TO PLAY" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Controls:" << endl;
    cout << "W - Full Thrust" << endl;
    cout << "X - Cut Engines" << endl;
    cout << "D - Throttle Up" << endl;
    cout << "A - Throttle Down" << endl;
    cout << "Q - Quit" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Gameplay Instructions:" << endl;
    cout << "1. When the game starts, the lander will immediately fall to the surface." << endl;
    cout << "2. If no action is taken, the lander will crash into the surface within a few seconds." << endl;
    cout << "3. Use the controls to slow the descent of the lander to a safe velocity." << endl;
    cout << "4. Different landers have varying thrust outputs, masses, and starting fuel levels." << endl;
    cout << "5. You can select different planets with unique gravitational pulls and surface characteristics." << endl;
    cout << "6. Aim to land the lander safely by managing your fuel and controlling your descent speed." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Objectives:" << endl;  
    cout << "1. The main goal is to land the lander safely on the planet's surface." << endl;
    cout << "2. Your final score is based on the remaining fuel and your landing speed." << endl;
    cout << "3. A higher remaining fuel indicates a more efficient landing." << endl;
    cout << "4. A lower landing speed results in a higher score, as long as the lander doesn't crash." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Lander Selection:" << endl;
    cout << "1. Different landers have different thrust outputs and masses." << endl;
    cout << "2. Choose a lander based on your preference for thrust and fuel capacity." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Planet Selection:" << endl;
    cout << "1. Each planet has a unique gravitational pull that affects your lander's descent." << endl;
    cout << "2. Planets also have different surface types that impact the difficulty of landing." << endl;
    //cout << "3. Atmosphere density is a factor, but it is currently an unfinished feature." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Advanced Tips:" << endl;
    cout << "1. Physics of Free Fall:" << endl;
    cout << "   - Position: The lander's current location in space." << endl;
    cout << "   - Velocity: The speed and direction of the lander's movement." << endl;
    cout << "   - Acceleration: The rate of change of velocity, influenced by gravity and thrust." << endl;
    cout << "   - Lithobraking: A very serious term meaning slowing down by hitting the ground (not recommended!)." << endl;
    cout << "2. Thrust and Fuel Depletion:" << endl;
    cout << "   - Thrust: Use the lander's engines to counteract gravity and control descent speed." << endl;
    cout << "   - Fuel Depletion: Be mindful of your fuel levels; efficient thrust use is crucial." << endl;
    cout << "3. Advanced Landing Techniques:" << endl;
    cout << "   - Suicide Burn: A strategy where you apply full thrust at the last moment to avoid a crash, minimizing fuel use." << endl;
    cout << "   - Feathering Thrust: Gradually adjust thrust to maintain a smooth deceleration." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Press any key to return to the Info menu." << endl;
    _getch();
    clearScreen();
    displayInfoMenu();
}
