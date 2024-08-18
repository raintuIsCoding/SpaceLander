#ifndef LANDERSCAROUSEL_H
#define LANDERSCAROUSEL_H

#include <map>
#include <string>
using namespace std;

void displayLandersCarousel();
void displayLandersPage(const string& landerName);
void confirmLandersSelection(const string& landerName);

// Map to store ASCII art for each lander
extern const map<string, string> landerArtMap;
extern double THRUST_FORCE; // Thrust force of the lander
extern double thrust;
extern float fuelLevel;
extern string selectedLander;

// Function to get the initial fuel level based on the selected lander
float getInitialFuelLevel(const string& landerName);

#endif // LANDERSCAROUSEL_H