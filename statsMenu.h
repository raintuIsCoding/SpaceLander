#ifndef STATSMENU_H
#define STATSMENU_H

using namespace std;

void displayStatsMenu();

string sanitizeName(const std::string& name);

void recordScore(const string& playerName, int finalScore, float finalVelocity, float remainingFuel);
void updateStats(const string& playerName, int finalScore, float finalVelocity, float remainingFuel);
void savePlayerName(const std::string& playerName);
string promptForPlayerName();
void createStatsDirectory();
string loadPlayerName();
void displayAskName();
void displayLandingResult(float finalVelocity, float remainingFuel, int finalScore);

#endif // STATSMENU_H