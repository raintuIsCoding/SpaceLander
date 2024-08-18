#ifndef SCREENUTILS_H
#define SCREENUTILS_H

#include <iostream>
#include <string>
#include <windows.h>  // For Windows-specific system calls

using namespace std;

// Function to clear the screen
void clearScreen();

// Function to get the width of the terminal window
int getTerminalWidth();

// Function to get the height of the terminal window
int getTerminalHeight();

// Function to print text centered
void printCentered(const string& text);

const int MIN_TERMINAL_WIDTH = 110;
const int MIN_TERMINAL_HEIGHT = 40;

#endif // SCREENUTILS_H
