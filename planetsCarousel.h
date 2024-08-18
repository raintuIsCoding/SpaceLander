#ifndef PLANETSCAROUSEL_H
#define PLANETSCAROUSEL_H

void displayPlanetsCarousel();
void displayPlanetsPage(const string& planetName);
void confirmPlanetSelection(const string& planetName);

// Map to store ASCII art for each lander
extern const map<string, string> planetArtMap;
extern double gravity;
extern double maxSurfaceLandingV;

#endif // PLANETSCAROUSEL_H