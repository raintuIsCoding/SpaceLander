#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <string>
#include "ScreenUtils.h"

using namespace std;

// Function to display the main menu
void displayMainMenu();
void displayStartGameInfo();

extern string selectedLander;
extern string selectedPlanet;

#endif // MAINMENU_H