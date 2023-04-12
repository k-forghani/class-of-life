#include <iostream>
#include "libs/common.h"
#include "libs/io.h"
#include "classes/Interface.h"

using namespace std;

Workspace wsp("CoL");

void start () {
    Interface interface(
        "Class of Life Command Line Interface (CoL CLI)",
        "0.9",
        "2023 Apr 12 16:07",
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
            // Add
            if (blocks.at(0) == "add") {
                if (blocks.at(1) == "genome") {
                    wsp.genomes[args.at("id").at(0)] = new Genome(
                        args.at("rna").at(0),
                        args.at("dna").at(0),
                        args.at("dna").at(1)
                    );
                } else if (blocks.at(1) == "chromosome") {
                    if (args.at("to").at(0) == "cell") {
                        wsp.cells[args.at("id").at(0)] -> addChromosome(
                            args.at("dna").at(0),
                            args.at("dna").at(1)
                        );
                    } else if (args.at("to").at(0) == "animal") {
                        wsp.animals[args.at("id").at(0)] -> addChromosome(
                            args.at("dna").at(0),
                            args.at("dna").at(1)
                        );
                    }
                } else if (blocks.at(1) == "cell") {
                    wsp.cells[args.at("id").at(0)] = new Cell(
                        stoi(args.at("number").at(0))
                    );
                } else if (blocks.at(1) == "animal") {
                    wsp.animals[args.at("id").at(0)] = new Animal(
                        stoi(args.at("number").at(0))
                    );
                } else if (blocks.at(1) == "virus") {
                    wsp.viruses[args.at("id").at(0)] = new Virus(
                        args.at("rna").at(0)
                    );
                }
                continue;
            // Load
            } else if (blocks.at(0) == "load") {
                map<string, string> records = parseFastA(args.at("from").at(0));
                if (blocks.at(1) == "genomes") {
                    map<string, map<string, string>> data;
                    for (auto &&i : records) {
                        vector<string> items = split(i.first, ' ');
                        if (data.count(items.at(0)) < 1) {
                            data[items.at(0)] = {};
                        }
                        data.at(items.at(0))[items.at(1)] = i.second;
                    }
                    for (auto &&i : data) {
                        wsp.genomes[i.first] = new Genome(
                            i.second.at("rna"),
                            i.second.at("dnaf"),
                            i.second.at("dnas")
                        );
                    }
                } else if (blocks.at(1) == "cells" || blocks.at(1) == "animals") {
                    map<string, map<string, map<string, string>>> data;
                    for (auto &&i : records) {
                        vector<string> items = split(i.first, ' ');
                        if (data.count(items.at(0)) < 1) {
                            data[items.at(0)] = {};
                        }
                        if (data.at(items.at(0)).count(items.at(1)) < 1) {
                            data.at(items.at(0))[items.at(1)] = {};
                        }
                        data.at(items.at(0)).at(items.at(1))[items.at(2)] = i.second;
                    }
                    for (auto &&i : data) {
                        if (blocks.at(1) == "cells") {
                            wsp.cells[i.first] = new Cell(i.second.size());
                            for (auto &&j : i.second) {
                                wsp.cells[i.first] -> addChromosome(
                                    j.second.at("1"),
                                    j.second.at("2")
                                );
                            }
                        } else if (blocks.at(1) == "animals") {
                            wsp.animals[i.first] = new Animal(i.second.size());
                            for (auto &&j : i.second) {
                                wsp.animals[i.first] -> addChromosome(
                                    j.second.at("1"),
                                    j.second.at("2")
                                );
                            }    
                        }
                    }
                } else if (blocks.at(1) == "viruses") {
                    for (auto &&i : records) {
                        vector<string> items = split(i.first, ' ');
                        wsp.viruses[items.at(0)] = new Virus(
                            i.second
                        );
                    }
                }
                continue;
            // Delete
            } else if (blocks.at(0) == "delete") {
                if (blocks.at(1) == "genome") {
                    wsp.genomes.erase(args.at("id").at(0));
                } else if (blocks.at(1) == "chromosome") {
                    if (args.at("from").at(0) == "cell") {
                        wsp.cells[args.at("id").at(0)] -> deleteChromosome(stoi(args.at("index").at(0)) - 1);
                    } else if (args.at("from").at(0) == "animal") {
                        wsp.animals[args.at("id").at(0)] -> deleteChromosome(stoi(args.at("index").at(0)) - 1);
                    }
                } else if (blocks.at(1) == "cell") {
                    wsp.cells.erase(args.at("id").at(0));
                } else if (blocks.at(1) == "animal") {
                    wsp.animals.erase(args.at("id").at(0));
                } else if (blocks.at(1) == "virus") {
                    wsp.viruses.erase(args.at("id").at(0));
                }
                continue;
            // Show
            } else if (blocks.at(0) == "show") {
                if (blocks.at(1) == "genome") {
                    wsp.showGenome(args.at("id").at(0), "extended");
                } else if (blocks.at(1) == "chromosome") {
                    wsp.showChromosome(
                        args.at("from").at(0),
                        args.at("id").at(0),
                        stoi(args.at("index").at(0)) - 1,
                        "extended"
                    );
                } else if (blocks.at(1) == "cell") {
                    wsp.showCell(args.at("id").at(0), "extended");
                } else if (blocks.at(1) == "animal") {
                    wsp.showAnimal(args.at("id").at(0), "extended");
                } else if (blocks.at(1) == "virus") {
                    wsp.showVirus(args.at("id").at(0), "extended");
                }
                continue;
            // List
            } else if (blocks.at(0) == "list") {
                if (blocks.at(1) == "genomes") {
                    wsp.listGenomes();
                } else if (blocks.at(1) == "cells") {
                    wsp.listCells();
                } else if (blocks.at(1) == "animals") {
                    wsp.listAnimals();
                } else if (blocks.at(1) == "viruses") {
                    wsp.listViruses();
                }
                continue;
            // Genomes
            } else if (blocks.at(0) == "genomes") {
                Genome* genome = wsp.genomes.at(args.at("id").at(0));
                if (blocks.at(1) == "transform") {
                    pair<Strand, Strand> dna = genome -> transformRNAtoDNA();
                    wsp.showPairOfStrands(dna, 0, true);
                } else if (blocks.at(1) == "mutate") {
                    if (blocks.at(2) == "rna") {
                        if (blocks.at(3) == "small") {
                            genome -> mutateSmallScaleRNA(
                                args.at("from").at(0)[0],
                                args.at("to").at(0)[0],
                                stoi(args.at("number").at(0))
                            );
                        } else if (blocks.at(3) == "large") {
                            genome -> mutateLargeScaleRNA(
                                args.at("from").at(0),
                                args.at("to").at(0)
                            );
                        } else if (blocks.at(3) == "inversely") {
                            genome -> mutateInverselyRNA(
                                args.at("on").at(0)
                            );
                        }
                    } else if (blocks.at(2) == "dna") {
                        if (blocks.at(3) == "small") {

                        } else if (blocks.at(3) == "large") {

                        } else if (blocks.at(3) == "inversely") {

                        }
                    }
                }
                continue;
            }
        }
        wsp.addLog(
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