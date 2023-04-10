#include <iostream>
#include "classes/Interface.h"

using namespace std;

int main () {
    srand(time(NULL));

    Workspace* workspace = new Workspace("CoL");
    Interface interface(
        "CoL CLI",
        "0.9",
        "2023 Apr 10 21:13",
        "A program to simply simulate some fundamental biological processes!",
        {
            "Kazem Forghani",
            "Elaheh Razmkhah"
        }
    );
    interface.showWelcome();
    
    while (true) {
        vector<string> blocks = interface.getCommand();
    }

    return 0;
}