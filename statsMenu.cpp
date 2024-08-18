// Default library
#include <iostream>

// *Menu headers
#include "mainMenu.h"
#include "startGame.h"
#include "statsMenu.h"
#include "infoMenu.h"

// *Screen utilities
#include "screenUtils.h"

// Gameplay utilities
#include <conio.h>      // For console input/output functions like _getch()
#include <ctime>        // For time-related functions like time() and localtime()
#include <fstream>      // For file operations like reading from and writing to files
#include <string>       // For using the string class for string manipulation
#include <windows.h>    // For Windows-specific functions like system() and GetConsoleScreenBufferInfo()
#include <sstream>      // For string stream operations like stringstream for converting between strings and other types
#include <filesystem>   // For filesystem operations (C++17 or later)
#include <vector>       // For using the vector container
#include <map>          // For using the map container
#include <chrono>       // For timekeeping and duration utilities
#include <cmath>        // For mathematical functions
#include <thread>       // For managing threads and thread sleep functions
#include <iomanip>      // For manipulating input/output formatting

using namespace std;
using namespace chrono;
namespace fs = filesystem;

// Function declarations
void clearScreen();
void flushInputBuffer();
void startGame();
void displayMainMenu();
void displayAskName();
string promptForPlayerName();
void savePlayerName(const string& playerName);
void recordScore(const string& playerName, int finalScore, float finalVelocity, float remainingFuel);
void updateStats(const string& playerName, int finalScore, float finalVelocity, float remainingFuel);
void displayStatsMenu();

// Function to sanitize the player's name
string sanitizeName(const string& name) {
    string sanitized = name;
    for (char& c : sanitized) {
        if (c == '<' || c == '>' || c == ':' || c == '"' || c == '/' || c == '\\' || c == '|' || c == '?' || c == '*') {
            c = '_'; // Replace invalid characters with '_'
        }
    }
    return sanitized;
}

void displayAskName() {
    cout << "Please enter your name (or leave empty to remain anonymous): ";
    string playerName;
    getline(cin, playerName);

    // Sanitize the name to avoid invalid characters in filenames
    playerName = sanitizeName(playerName);

    if (playerName.empty()) {
        playerName = "Anonymous Pilot";
        savePlayerName(playerName);
    }
}

// Function to record the score to a file
void recordScore(const string& playerName, int finalScore, float finalVelocity, float remainingFuel) {
    fs::path scoresFile = fs::path("Stats") / "Scores_Stats.txt";
    ofstream file(scoresFile, ios::app);
    if (file.is_open()) {
        auto t = time(nullptr);
        auto tm = *localtime(&t);

        file << "Pilot: " << playerName << ", final score: " << finalScore << " points, landing velocity: " 
             << setprecision(2) << finalVelocity << " m/s, leftover fuel: " << setprecision(2) << remainingFuel 
             << " ML. Recorded on " << put_time(&tm, "%Y-%m-%d %H:%M:%S") << endl;
        file.close();
    } else {
        cerr << "Error opening scores file!" << endl;
    }
}

void updateStats(const string& playerName, int finalScore, float finalVelocity, float remainingFuel) {
    fs::path statsFile = fs::path("Stats") / "Store_Player_Stats.txt";
    map<string, vector<float>> stats;
    ifstream file(statsFile);
    string line;

    // Read existing stats
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            string name;
            float score, velocity, fuel;
            int attempts;
            float avgScore;
            if (iss >> name >> score >> velocity >> fuel >> attempts >> avgScore) {
                stats[name] = {score, velocity, fuel, static_cast<float>(attempts), avgScore};
            }
        }
        file.close();
    }

    // Update the player's stats
    if (stats.find(playerName) != stats.end()) {
        stats[playerName][0] = max(stats[playerName][0], static_cast<float>(finalScore));
        stats[playerName][1] = min(stats[playerName][1], finalVelocity);
        stats[playerName][2] = max(stats[playerName][2], remainingFuel);
        stats[playerName][3] += 1;
        stats[playerName][4] = (stats[playerName][4] * (stats[playerName][3] - 1) + finalScore) / stats[playerName][3];
    } else {
        stats[playerName] = {static_cast<float>(finalScore), finalVelocity, remainingFuel, 1, static_cast<float>(finalScore)};
    }

    // Write updated stats back to file
    ofstream outFile(statsFile);
    if (outFile.is_open()) {
        for (const auto& pair : stats) {
            outFile << pair.first << " " << pair.second[0] << " " << pair.second[1] << " " << pair.second[2] << " " 
                    << pair.second[3] << " " << pair.second[4] << endl;
        }
        outFile.close();
    } else {
        cerr << "Error opening stats file!" << endl;
    }
}

// Function to save player's name to a file
void savePlayerName(const string& playerName) {
    fs::path nameFile = fs::path("Stats") / "Store_Player_Name.txt";
    ofstream file(nameFile);
    if (file.is_open()) {
        file << playerName;
        file.close();
    } else {
        cerr << "Error opening player name file!" << endl;
    }
}

// Function to load player's name from a file
string loadPlayerName() {
    fs::path nameFile = fs::path("Stats") / "Store_Player_Name.txt";
    ifstream file(nameFile);
    string playerName;
    if (file.is_open()) {
        getline(file, playerName);
        file.close();
    }
    return playerName;
}

// Function to prompt player for their name
string promptForPlayerName() {
    string playerName;
    cout << " Please enter your name (or leave empty to remain anonymous): ";
    getline(cin, playerName);
    cout << endl;
    if (playerName.empty()) {
        playerName = "Anonymous Pilot";
    }
    playerName = sanitizeName(playerName);
    savePlayerName(playerName);
    return playerName;
}

// Function to display scores from the file
void displayScores() {
    fs::path scoresFile = fs::path("Stats") / "Scores_Stats.txt";
    ifstream file(scoresFile);
    string line;

    if (file.is_open()) {
        cout << "Scores:" << endl;
        cout << "--------------------------" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No scores available. Play the game to view scores!" << endl;
    }
}

// Function to display player statistics from the file
void displayPlayerStats() {
    fs::path statsFile = fs::path("Stats") / "Store_Player_Stats.txt";
    ifstream file(statsFile);
    string line;

    if (file.is_open()) {
        cout << "Player Statistics:" << endl;
        cout << "--------------------------" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No player statistics available. Play the game to view stats!" << endl;
    }
}

// Function to display the stats menu
void displayStatsMenu() {
    char choice;
    clearScreen();

    cout << "Stats Menu:" << endl;
    cout << "1) View Scores" << endl;
    cout << "2) View Player Statistics" << endl;
    cout << "3) Go Back to Main Menu" << endl;
    cout << "Please select an option (1-3): ";

    choice = _getch();
    switch (choice) {
        case '1':
            clearScreen();
            displayScores();
            break;
        case '2':
            clearScreen();
            displayPlayerStats();
            break;
        case '3':
            clearScreen();
            displayMainMenu();
            break;
        default:
            cout << "Invalid option. Please select a number between 1 and 3." << endl;
            _getch();
            displayStatsMenu();
            break;
    }

    cout << "\nPress any key to return to the Stats Menu...";
    _getch();
    displayStatsMenu();
}
void createStatsDirectory() {
    // Create the `Stats` directory if it doesn't exist
    fs::path statsDir("Stats");
    if (!fs::exists(statsDir)) {
        fs::create_directory(statsDir);
    }
}
