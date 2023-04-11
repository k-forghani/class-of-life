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
        map<string, vector<string>> args;
        string latest = "";
        for (auto &&i : blocks) {
            if (i[0] == '-') {
                latest = i.substr(1, i.length() - 1);
                args[latest] = {};
            } else if (latest != "") {
                args[latest].push_back(i);
            }
        }       
        
        if (blocks.size() == 1) {
            if (blocks.at(0) == "clear") {
                interface.clearScreen();
                start();
                continue;
            } else if (blocks.at(0) == "about") {
                interface.showAbout();
                continue;
            } else if (blocks.at(0) == "help") {
                interface.showHelp(
                    Text("Coming soon!")
                );
                continue;
            } else if (blocks.at(0) == "exit") {
                exit(0);
                continue;
            }
        } else if (blocks.size() > 1) {
            if (blocks.at(0) == "add") {
                if (blocks.at(1) == "genome") {
                    workspace.genomes[args.at("id").at(0)] = new Genome(
                        args.at("rna").at(0),
                        args.at("dna").at(0),
                        args.at("dna").at(1)
                    );
                } else if (blocks.at(1) == "chromosome") {
                    if (args.at("to").at(0) == "cell") {
                        workspace.cells[args.at("id").at(0)] -> addChromosome(
                            args.at("dna").at(0),
                            args.at("dna").at(1)
                        );
                    } else if (args.at("to").at(0) == "animal") {
                        workspace.animals[args.at("id").at(0)] -> addChromosome(
                            args.at("dna").at(0),
                            args.at("dna").at(1)
                        );
                    }
                } else if (blocks.at(1) == "cell") {
                    workspace.cells[args.at("id").at(0)] = new Cell(
                        stoi(args.at("number").at(0))
                    );
                } else if (blocks.at(1) == "animal") {
                    workspace.animals[args.at("id").at(0)] = new Animal(
                        stoi(args.at("number").at(0))
                    );
                } else if (blocks.at(1) == "virus") {
                    workspace.viruses[args.at("id").at(0)] = new Virus(
                        args.at("rna").at(0)
                    );
                }
                continue;
            } else if (blocks.at(0) == "delete") {
                if (blocks.at(1) == "genome") {
                    workspace.genomes.erase(args.at("id").at(0));
                } else if (blocks.at(1) == "chromosome") {
                    if (args.at("from").at(0) == "cell") {
                        workspace.cells[args.at("id").at(0)] -> deleteChromosome(stoi(args.at("index").at(0)));
                    } else if (args.at("from").at(0) == "animal") {
                        workspace.animals[args.at("id").at(0)] -> deleteChromosome(stoi(args.at("index").at(0)));
                    }
                } else if (blocks.at(1) == "cell") {
                    workspace.cells.erase(args.at("id").at(0));
                } else if (blocks.at(1) == "animal") {
                    workspace.animals.erase(args.at("id").at(0));
                } else if (blocks.at(1) == "virus") {
                    workspace.viruses.erase(args.at("id").at(0));
                }
                continue;
            } else if (blocks.at(0) == "show") {
                if (blocks.at(1) == "genome") {
                    workspace.showGenome(args.at("id").at(0), "extended");
                } else if (blocks.at(1) == "chromosome") {
                    workspace.showChromosome(
                        args.at("from").at(0),
                        args.at("id").at(0),
                        stoi(args.at("index").at(0)),
                        "extended"
                    );
                } else if (blocks.at(1) == "cell") {
                    workspace.showCell(args.at("id").at(0), "extended");
                } else if (blocks.at(1) == "animal") {
                    workspace.showAnimal(args.at("id").at(0), "extended");
                } else if (blocks.at(1) == "virus") {
                    workspace.showVirus(args.at("id").at(0), "extended");
                }
                continue;
            }
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