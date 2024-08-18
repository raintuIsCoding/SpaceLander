//Default library
#include <iostream>

//*Menu headers
#include "startScreen.h"
#include "mainMenu.h"

//*Screen utilities
#include "screenUtils.h"

//Gameplay utilities
#include <conio.h> //For console input/output functions like _getch()

using namespace std;

int main() {
    displayStartScreen();
    _getch();
    displayMainMenu();
    return 0;
}