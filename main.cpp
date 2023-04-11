#include <iostream>
#include "libs/common.h"
#include "classes/Interface.h"

using namespace std;

Workspace workspace("CoL");

void start () {
    Interface interface(
        "Class of Life Command Line Interface (CoL CLI)",
        "0.9",
        "2023 Apr 11 12:23",
        "A program to simply simulate some fundamental biological processes!",
        {
            "Kazem Forghani",
            "Elaheh Razmkhah"
        }
    );
    interface.showWelcome();
    
    while (true) {
        vector<string> blocks = interface.getCommand();
        if (blocks.size() == 1) {
            string c1 = tolower(blocks.at(0));
            if (c1 == "clear") {
                interface.clearScreen();
                start();
                continue;
            } else if (c1 == "about") {
                interface.showAbout();
                continue;
            } else if (c1 == "help") {
                interface.showHelp(
                    Text("Coming soon!")
                );
                continue;
            } else if (c1 == "exit") {
                exit(0);
                continue;
            }
        } else if (blocks.size() > 1) {
            
        }
        workspace.addLog(
            "ERROR",
            new Text("Invalid command!")
        );
    }
}

int main () {
    srand(time(NULL));
    
    start();

    return 0;
}