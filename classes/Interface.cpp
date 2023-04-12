#include <iostream>
#include "../libs/common.h"
#include "Interface.h"

using namespace std;

/* Text */

Text::Text (string text, string foreground, string background, set<string> modes) {
    this -> text = text;
    this -> foreground = foreground;
    this -> background = background;
    this -> modes = modes;
    render();
}

void Text::render () {
    if (foreground != "" || background != "" || modes.size() > 0) {
        #if __linux__
            output = ESCAPE + CONTROL;

            if (foreground != "") {
                output += COLORS.at(foreground).first + SEPARATOR;
            }

            if (background != "") {
                output += COLORS.at(background).second + SEPARATOR;
            }

            for (auto &&i : modes) {
                output += MODES.at(i).first + SEPARATOR;
            }
            
            output = output.substr(0, output.length() - 1) + END;
            output += text;
            output += ESCAPE + CONTROL + RESET + END;
        #else
            output = text;
        #endif
    } else {
        output = text;
    }
}

void Text::changeText (string text) {
    this -> text = text;
    Text::render();
}

void Text::changeForeground (string foreground) {
    this -> foreground = foreground;
    Text::render();
}

void Text::changeBackground (string background) {
    this -> background = background;
    Text::render();
}

void Text::changeModes (set<string> modes) {
    this -> modes = modes;
    Text::render();
}

ostream& operator<< (ostream& output, const Text& text) {
    output << text.output;
    return output;
}

istream& operator>> (istream& input, Text& text) {
    string content;
    getline(input, content);
    text.changeText(content);
    return input;
}

Text operator+ (const Text& t1, const Text& t2) {
    return Text(t1.output + t2.output);
}

/* Log */

Log::Log (string type, Text* text) {
    this -> type = toupper(type);
    this -> text = text;
}

void Log::print (bool type) const {
    if (type) {
        string color = COLORS.at(this -> type);
        cout << Text(this -> type, color) << " ";
    }
    cout << *text << endl;
}

/* Workspace */

Workspace::Workspace (string root) {
    this -> root = root;
}

void Workspace::addLog (string type, Text* text, bool print) {
    Log log(type, text);
    logs.push_back(log);
    if (print)
        log.print();
}

void Workspace::showStrand (const Strand& strand, int indent, bool numbers, int length) const {
    string content = strand.getStrand();

    if (content.length() <= length) {
        numbers = false;
    }

    int number = 1;

    for (int j = 0; j < content.length(); j++) {
        int segment = (j + 1) % length;
        if (segment == 0 || j == content.length() - 1) {
            if (segment == 0) {
                segment = length;
            }
            cout << string(indent, '\t');
            if (numbers) {
                cout << Text(to_string(number), "", "", {"dim"}) << " ";
            }
            cout << Text(content.substr(j - segment + 1, segment)) << endl;
            number++;
        }
    }
}

void Workspace::showStrandSummary (const Strand& strand, int length) const {
    string content = strand.getStrand();

    if (content.length() == length) {
        cout << Text(content);
    } else if (content.length() > length) {
        cout << Text(content.substr(0, length - 4) + " ...");
    } else {
        cout << Text(content) << string(length - content.length(), ' ');
    }
}

void Workspace::showPairOfStrands (const pair<Strand, Strand>& strands, int indent, bool numbers, int length) const {
    cout << string(indent, '\t') << Text("First Strand", "", "", {"dim", "bold"}) << endl;
    Workspace::showStrand(strands.first, indent + 1, numbers);
    cout << string(indent, '\t') << Text("Second Strand", "", "", {"dim", "bold"}) << endl;
    Workspace::showStrand(strands.second, indent + 1, numbers);
}

void Workspace::showGenome (string id, string mode) const {
    Genome* genome = genomes.at(id);
    
    if (mode == "extended") {
        cout << Text("ID", "", "", {"dim", "bold"}) << endl;
        cout << "\t" << Text(id) << endl;
        cout << Text("RNA", "", "", {"dim", "bold"}) << endl;
        Workspace::showStrand(genome -> getRNA(), 1, true);
        cout << Text("DNA", "", "", {"dim", "bold"}) << endl;
        Workspace::showPairOfStrands(genome -> getDNA(), 1, true);
    } else if (mode == "compact") {
        cout << Text(id) << Text(" | ", "", "", {"dim", "bold"});
        showStrandSummary(genome -> getRNA());
        cout << Text(" | ", "", "", {"dim", "bold"});
        showStrandSummary((genome -> getDNA()).first);
        cout << Text(" | ", "", "", {"dim", "bold"});
        showStrandSummary((genome -> getDNA()).second);
        cout << endl;
    }
}

void Workspace::showChromosome (string from, string id, int index, string mode) const {
    vector<Chromosome*> chromosomes;
    if (from == "cell") {
        chromosomes = cells.at(from) -> getChromosomes();
    } else if (from == "animal") {
        chromosomes = animals.at(from) -> getChromosomes();
    }
    if (chromosomes.size() > 0) {
        Chromosome* c = chromosomes.at(index);
        if (mode == "extended") {
            cout << Text("ID", "", "", {"dim", "bold"}) << endl;
            cout << "\t" << Text(id) << endl;
            cout << Text("DNA", "", "", {"dim", "bold"}) << endl;
            Workspace::showPairOfStrands(c -> getDNA(), 1, true);
        } else if (mode == "compact") {
            cout << Text(id) << Text(" | ", "", "", {"dim", "bold"});
            showStrandSummary((c -> getDNA()).first);
            cout << Text(" | ", "", "", {"dim", "bold"});
            showStrandSummary((c -> getDNA()).second);
            cout << endl;
        }
    }
}

void Workspace::showCell (string id, string mode) const {
    Cell* cell = cells.at(id);

    if (mode == "extended") {
        cout << Text("ID", "", "", {"dim", "bold"}) << endl;
        cout << "\t" << Text(id) << endl;
        int counter = 0;
        for (auto &&c : cell -> getChromosomes()) {
            counter++;
            cout << Text("Chromosome " + to_string(counter), "", "", {"dim", "bold"}) << endl;
            Workspace::showPairOfStrands(c -> getDNA(), 1, true);
        }
    } else if (mode == "compact") {
        cout << Text(id) << Text(" | ", "", "", {"dim", "bold"});
        cout << Text(to_string((cell -> getChromosomes()).size())) << Text(" Chromosomes") << endl;
    }
}

void Workspace::showAnimal (string id, string mode) const {
    Cell* animal = animals.at(id);

    if (mode == "extended") {
        cout << Text("ID", "", "", {"dim", "bold"}) << endl;
        cout << "\t" << Text(id) << endl;
        int counter = 0;
        for (auto &&c : animal -> getChromosomes()) {
            counter++;
            cout << Text("Chromosome " + to_string(counter), "", "", {"dim", "bold"}) << endl;
            Workspace::showPairOfStrands(c -> getDNA(), 1, true);
        }
    } else if (mode == "compact") {
        cout << Text(id) << Text(" | ", "", "", {"dim", "bold"});
        cout << Text(to_string((animal -> getChromosomes()).size())) << Text(" Chromosomes") << endl;
    }
}

void Workspace::showVirus (string id, string mode) const {
    Virus* virus = viruses.at(id);
    
    if (mode == "extended") {
        cout << Text("ID", "", "", {"dim", "bold"}) << endl;
        cout << "\t" << Text(id) << endl;
        cout << Text("RNA", "", "", {"dim", "bold"}) << endl;
        Workspace::showStrand(virus -> getRNA(), 1, true);
    } else if (mode == "compact") {
        cout << Text(id) << Text(" | ", "", "", {"dim", "bold"});
        showStrandSummary(virus -> getRNA());
        cout << endl;
    }
}

void Workspace::listGenomes () const {
    for (auto &&i : genomes) {
        Workspace::showGenome(i.first, "compact");
    }
}

void Workspace::listCells () const {
    for (auto &&i : cells) {
        Workspace::showCell(i.first, "compact");
    }
}

void Workspace::listAnimals () const {
    for (auto &&i : animals) {
        Workspace::showAnimal(i.first, "compact");
    }
}

void Workspace::listViruses () const {
    for (auto &&i : viruses) {
        Workspace::showVirus(i.first, "compact");
    }
}

/* Interface */

Interface::Interface (
    string name,
    string version,
    string datetime,
    string description,
    vector<string> authors
) : name(name), version(version), datetime(datetime), description(description), authors(authors) {}

void Interface::cleanInput () const {
    cin.clear();
    cin.ignore(10000, '\n');
}

void Interface::clearScreen () const {
    #if __linux__
        system("clear");
    #elif _WIN32
        system("CLS");
    #else
        cout << "\033[L";
    #endif
}

vector<string> Interface::handleCommand (string command) const {
    cout << Text(">>>", "green", "", {"dim"}) << " ";
    if (command == "") {
        getline(cin, command);
    } else {
        cout << Text(command, "", "", {"dim"}) << endl;
    }
    vector<string> blocks;
    int previous = -1;
    bool quotation = false;
    for (int i = 0; i < command.length(); i++) {
        if (command[i] == ' ' && !quotation) {
            if (i - previous - 1 != 0) {
                blocks.push_back(
                    command.substr(previous + 1, i - previous - 1)
                );
            }
            previous = i;
        } else if (command[i] == '"' || command[i] == '\'') {
            if (quotation) {
                if (i - previous - 1 != 0) {
                    blocks.push_back(
                        command.substr(previous + 1, i - previous - 1)
                    );
                }
            }
            previous = i;
            quotation = !quotation;
        } else if (i == command.length() - 1) {
            if (i - previous != 0) {
                blocks.push_back(
                    command.substr(previous + 1, i - previous)
                );
            }
        }
    }
    return blocks;
}

void Interface::showWelcome () const {
    cout << Text("Name:") << " " << Text(name) << endl;
    cout << Text("Version:") << " " << Text(version) << endl;
    cout << Text(description) << endl;
}

void Interface::showAbout () const {
    cout << Text("Coming soon!") << endl;
}

void Interface::showHelp (const Text& information) const {
    cout << information << endl;
}