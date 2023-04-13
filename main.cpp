#include <iostream>
#include "libs/common.h"
#include "libs/io.h"
#include "classes/Interface.h"

using namespace std;

// Functions Declarations

string booleanToString(bool value);
void perform(vector<string> blocks);
void start();

// Global Variables

Workspace wsp("CoL");
Interface interface(
    "Class of Life Command Line Interface (CoL CLI)",
    "0.9 BETA",
    "2023 Apr 13 01:15",
    "A program to simply simulate some fundamental biological processes!",
    "https://github.com/k-forghani/class-of-life",
    {
        "Kazem Forghani",
        "Elaheh Razmkhah"
    }
);

// Functions Definitions

string booleanToString (bool value) {
    if (value) {
        return "true";
    } else {
        return "false";
    }
}

void perform (vector<string> blocks) {
    try {
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

        if (blocks.size() == 0) {
            return;
        } else if (blocks.size() == 1) {
            if (blocks.at(0) == "clear") {
                interface.clearScreen();
                start();
                return;
            } else if (blocks.at(0) == "about") {
                interface.showAbout();
                return;
            } else if (blocks.at(0) == "help") {
                cout << Text("Please take a look at examples folder.") << endl;
                return;
            } else if (blocks.at(0) == "exit") {
                exit(0);
                return;
            }
        } else {
            // Add
            if (blocks.at(0) == "run") {
                vector<string> commands = readLines(blocks.at(1));
                for (auto &&i : commands) {
                    vector<string> blocks = interface.handleCommand(i);
                    perform(blocks);
                }
                return;
            } else if (blocks.at(0) == "add") {
                if (blocks.at(1) == "genome") {
                    wsp.genomes[args.at("id").at(0)] = new Genome(
                        args.at("rna").at(0),
                        args.at("dna").at(0),
                        args.at("dna").at(1)
                    );
                    return;
                } else if (blocks.at(1) == "chromosome") {
                    if (args.at("to").at(0) == "cell") {
                        wsp.cells[args.at("id").at(0)] -> addChromosome(
                            args.at("dna").at(0),
                            args.at("dna").at(1)
                        );
                        return;
                    } else if (args.at("to").at(0) == "animal") {
                        wsp.animals[args.at("id").at(0)] -> addChromosome(
                            args.at("dna").at(0),
                            args.at("dna").at(1)
                        );
                        return;
                    }
                } else if (blocks.at(1) == "cell") {
                    wsp.cells[args.at("id").at(0)] = new Cell(
                        stoi(args.at("number").at(0))
                    );
                    return;
                } else if (blocks.at(1) == "animal") {
                    wsp.animals[args.at("id").at(0)] = new Animal(
                        stoi(args.at("number").at(0))
                    );
                    return;
                } else if (blocks.at(1) == "virus") {
                    wsp.viruses[args.at("id").at(0)] = new Virus(
                        args.at("rna").at(0)
                    );
                    return;
                }
                return;
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
                    return;
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
                    return;
                } else if (blocks.at(1) == "viruses") {
                    for (auto &&i : records) {
                        vector<string> items = split(i.first, ' ');
                        wsp.viruses[items.at(0)] = new Virus(
                            i.second
                        );
                    }
                    return;
                }
            // Delete
            } else if (blocks.at(0) == "delete") {
                if (blocks.at(1) == "genome") {
                    wsp.genomes.erase(args.at("id").at(0));
                    return;
                } else if (blocks.at(1) == "chromosome") {
                    if (args.at("from").at(0) == "cell") {
                        wsp.cells[args.at("id").at(0)] -> deleteChromosome(stoi(args.at("index").at(0)) - 1);
                        return;
                    } else if (args.at("from").at(0) == "animal") {
                        wsp.animals[args.at("id").at(0)] -> deleteChromosome(stoi(args.at("index").at(0)) - 1);
                        return;
                    }
                } else if (blocks.at(1) == "cell") {
                    wsp.cells.erase(args.at("id").at(0));
                    return;
                } else if (blocks.at(1) == "animal") {
                    wsp.animals.erase(args.at("id").at(0));
                    return;
                } else if (blocks.at(1) == "virus") {
                    wsp.viruses.erase(args.at("id").at(0));
                    return;
                }
            // Show
            } else if (blocks.at(0) == "show") {
                if (blocks.at(1) == "genome") {
                    wsp.showGenome(args.at("id").at(0), "extended");
                    return;
                } else if (blocks.at(1) == "chromosome") {
                    wsp.showChromosome(
                        args.at("from").at(0),
                        args.at("id").at(0),
                        stoi(args.at("index").at(0)) - 1,
                        "extended"
                    );
                    return;
                } else if (blocks.at(1) == "cell") {
                    wsp.showCell(args.at("id").at(0), "extended");
                    return;
                } else if (blocks.at(1) == "animal") {
                    wsp.showAnimal(args.at("id").at(0), "extended");
                    return;
                } else if (blocks.at(1) == "virus") {
                    wsp.showVirus(args.at("id").at(0), "extended");
                    return;
                }
            // List
            } else if (blocks.at(0) == "list") {
                if (blocks.at(1) == "genomes") {
                    wsp.listGenomes();
                    return;
                } else if (blocks.at(1) == "cells") {
                    wsp.listCells();
                    return;
                } else if (blocks.at(1) == "animals") {
                    wsp.listAnimals();
                    return;
                } else if (blocks.at(1) == "viruses") {
                    wsp.listViruses();
                    return;
                }
            // Genomes
            } else if (blocks.at(0) == "genomes") {
                Genome* genome = wsp.genomes.at(args.at("id").at(0));
                if (blocks.at(1) == "transform") {
                    pair<Strand, Strand> dna = genome -> transformRNAtoDNA();
                    wsp.showPairOfStrands(dna, 0, true);
                    return;
                } else if (blocks.at(1) == "mutate") {
                    if (blocks.at(2) == "rna") {
                        if (blocks.at(3) == "small") {
                            genome -> mutateSmallScaleRNA(
                                args.at("from").at(0)[0],
                                args.at("to").at(0)[0],
                                stoi(args.at("number").at(0))
                            );
                            return;
                        } else if (blocks.at(3) == "large") {
                            genome -> mutateLargeScaleRNA(
                                args.at("from").at(0),
                                args.at("to").at(0)
                            );
                            return;
                        } else if (blocks.at(3) == "inversely") {
                            genome -> mutateInverselyRNA(
                                args.at("on").at(0)
                            );
                            return;
                        }
                    } else if (blocks.at(2) == "dna") {
                        if (blocks.at(3) == "small") { 
                            genome -> mutateSmallScaleDNA(
                                args.at("from").at(0)[0], 
                                args.at("to").at(0)[0],
                                stoi(args.at("number").at(0))
                            );
                            return;
                        } else if (blocks.at(3) == "large") { 
                            genome -> mutateLargeScaleDNA(
                                args.at("from").at(0),
                                args.at("to").at(0)
                            );
                            return;
                        } else if (blocks.at(3) == "inversely") { 
                            genome -> mutateInverselyDNA(
                                args.at("on").at(0)
                            );
                            return;
                        }
                    }
                }
            // Cells and Animals
            } else if (blocks.at(0) == "cells" || blocks.at(0) == "animals") {
                if (blocks.at(1) == "mutate" || blocks.at(1) == "palindromes" || blocks.at(1) == "die") {
                    Cell* cursor;
                    if (blocks.at(0) == "cells") {
                        cursor = wsp.cells.at(args.at("id").at(0));
                    } else {
                        cursor = wsp.animals.at(args.at("id").at(0));
                    }
                    
                    if (blocks.at(1) == "mutate") {
                        if (blocks.at(2) == "small") {
                            cursor -> mutateSmallScale(
                                args.at("from").at(0)[0],
                                args.at("to").at(0)[0],
                                stoi(args.at("chromosome").at(0)) - 1,
                                stoi(args.at("number").at(0))
                            );
                            return;
                        } else if (blocks.at(2) == "large") {
                            cursor -> mutateLargeScale(
                                args.at("from").at(1),
                                stoi(args.at("from").at(0)) - 1,
                                args.at("to").at(1),
                                stoi(args.at("to").at(0)) - 1
                            );
                            return;
                        } else if (blocks.at(2) == "inversely") {
                            cursor -> mutateInversely(
                                args.at("on").at(1),
                                stoi(args.at("on").at(0)) - 1
                            );
                            return;
                        }
                    } else if (blocks.at(1) == "palindromes") {
                        vector<vector<string>> result = cursor -> getComplementaryPalindromes();
                        string chromosome_index = "0";
                        string strand_index = "0";
                        for (auto &&i : result) {
                            if (i.at(0) != chromosome_index) {
                                cout << Text("Chromosome " + i.at(0), "", "", {"dim", "bold"}) << endl;
                                chromosome_index = i.at(0);
                            }
                            if (i.at(1) != strand_index) {
                                if (i.at(1) == "1") {
                                    cout << Text("\tFirst Strand", "", "", {"dim", "bold"}) << endl;
                                } else {
                                    cout << Text("\tSecond Strand", "", "", {"dim", "bold"}) << endl;
                                }
                                strand_index = i.at(1);
                            }
                            cout << Text("\t\t" + i.at(2) + "-" + i.at(3) + "\t" + i.at(4)) << endl;
                        }
                        return;
                    } else if (blocks.at(1) == "die") {
                        if (cursor -> dieIfShould()) {
                            if (blocks.at(0) == "cells") {
                                wsp.cells.erase(args.at("id").at(0));
                            } else {
                                wsp.animals.erase(args.at("id").at(0));
                            }
                        }
                        return;
                    }
                } else if (blocks.at(0) == "animals") {
                    if (blocks.at(1) == "similarity") {
                        Animal* a1 = wsp.animals.at(blocks.at(2));
                        Animal* a2 = wsp.animals.at(blocks.at(3));
                        cout << Text(to_string(a1 -> getGeneticSimilarity(*a2))) << endl;
                        return;
                    } else if (blocks.at(1) == "equality") {
                        Animal* a1 = wsp.animals.at(blocks.at(2));
                        Animal* a2 = wsp.animals.at(blocks.at(3));
                        cout << Text(booleanToString(a1 == a2)) << endl;
                        return;
                    } else if (blocks.at(1) == "reproduce") {
                        if (blocks.size() == 5) {
                            Animal* animal = wsp.animals.at(blocks.at(2));
                            wsp.animals[args.at("id").at(0)] = animal -> reproduceAsexually();
                            return;
                        } else if (blocks.size() == 6) {
                            Animal* a1 = wsp.animals.at(blocks.at(2));
                            Animal* a2 = wsp.animals.at(blocks.at(3));
                            wsp.animals[args.at("id").at(0)] = *a1 + *a2;
                            return;
                        }
                    } else if (blocks.at(1) == "kill" && blocks.at(2) == "chromosomes") {
                        wsp.animals[args.at("id").at(0)] -> killBadChromosomes();
                        return;
                    }
                }
            // Viruses
            } else if (blocks.at(0) == "viruses") {
                Virus* virus = wsp.viruses.at(args.at("id").at(0));
                if (blocks.at(1) == "mutate") {
                    if (blocks.at(2) == "small") {
                        virus -> mutateSmallScale(
                            args.at("from").at(0)[0],
                            args.at("to").at(0)[0],
                            stoi(args.at("number").at(0))
                        );
                        return;
                    } else if (blocks.at(2) == "large") {
                        virus -> mutateLargeScale(
                            args.at("from").at(0),
                            args.at("to").at(0)
                        );
                        return;
                    } else if (blocks.at(2) == "inversely") {
                        virus -> mutateInversely(
                            args.at("on").at(0)
                        );
                        return;
                    }
                } else if (blocks.at(1) == "pathogenicity") {
                    Animal animal = *wsp.animals.at(args.at("for").at(0));
                    cout << Text(booleanToString(virus -> isPathogenic(animal))) << endl;
                    return;
                }
            }
        }
        wsp.addLog(
            "ERROR",
            new Text("Invalid command!")
        );
    } catch (const exception& error) {
        wsp.addLog(
            "ERROR",
            new Text(error.what())
        );
    }
}

void start () {
    interface.showWelcome();
    
    while (true) {
        vector<string> blocks = interface.handleCommand();
        perform(blocks);
    }
}

int main () {
    srand(time(NULL));
    
    start();

    return 0;
}