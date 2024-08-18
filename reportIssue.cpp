// Default library
#include <iostream>

// *Menu headers
#include "infoMenu.h"
#include "reportIssue.h"

// *Screen utilities
#include "screenUtils.h"

// Gameplay utilities
#include <ctime>        // For time-related functions like time() and localtime()
#include <fstream>      // For file operations like reading from and writing to files
#include <string>       // For using the std::string class for string manipulation
#include <sstream>      // For string stream operations like std::stringstream for converting between strings and other types
#include <filesystem>   // For filesystem operations (C++17 or later)
#include <windows.h>    // For Windows-specific functions like system() and GetConsoleScreenBufferInfo()

using namespace std;
namespace fs = std::filesystem; // Namespace for filesystem operations

void reportAnIssue() {
    clearScreen();
    string name;
    string issue;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    char time[6];

    // Format date and time
    sprintf(date, "%d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    sprintf(time, "%02d%02d", ltm->tm_hour, ltm->tm_min);

    // Pre-report screen for name query
    cout << "Before you tell me about your issue, what is your name? ";
    getline(cin, name);

    // Sanitize the name to avoid invalid characters in filenames
    for (char& c : name) {
        if (c == '<' || c == '>' || c == ':' || c == '"' || c == '/' || c == '\\' || c == '|' || c == '?' || c == '*') {
            c = '_'; // Replace invalid characters with '_'
        }
    }

    // Report screen
    clearScreen();
    cout << "Thank you, " << name << ". Go ahead and let us know in 250 characters or less what issue(s) you found!" << endl;
    cout << "You can hit Enter at any time to finalize and submit your report." << endl;
    getline(cin, issue);
    
    //Limit the issue description to 250 characters
    if (issue.empty()) {
        cout << "No issue reported. Please provide a description." << endl;
        Sleep(2000); //Pause for 2000 milliseconds (2 seconds)
        clearScreen();
        displayInfoMenu();
        return;
    }
    if (issue.length() > 250) {
        issue = issue.substr(0, 250);
    }

    //Create the `Reports` directory if it doesn't exist
    fs::path reportsDir("Reports");
    if (!fs::exists(reportsDir)) {
        fs::create_directory(reportsDir);
    }
    
    //Create the filename
    string filename = "Reports/" + name + "_" + date + "_" + time + ".txt";

    //Write the issue to the file
    ofstream reportFile(filename);
    if (!reportFile) {
        cout << "Unable to open file for writing: " << filename << endl;
        Sleep(2500); //Pause for 2.5 seconds
        clearScreen();
        displayInfoMenu();
        return;
    }

    //Ensuring the issue is written to the file
    reportFile << issue;
    reportFile.close();

    //Thank you message
    clearScreen();
    cout << "Thank you for your report, " << name << "!" << endl;
    cout << "We appreciate your feedback and will look into the issue." << endl;
    Sleep(2500);  //Pause for 2.5 seconds

    //Return to Info menu
    clearScreen();
    displayInfoMenu();
}
