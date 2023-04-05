#include <iostream>
#include <fstream>
#include "../libs/common.h"
#include "Interface.h"

using namespace std;

/* FastA */

FastA::FastA (string path) {
    this -> path = path;
}

void FastA::write (map<string, string> records, int length) const {
    ofstream fout(path);
    
    for (const auto &i : records) {
        string id = strip(i.first);
        string seq = divide(i.second, length);
        fout << ">" << id << "\n" << seq << "\n";
    }
    
    fout.close();
}

map<string, string> FastA::parse () const {
    ifstream fin(path);

    if (!fin.is_open()) {
        return {};
    }

    map<string, string> records;

    string latest = "";

    string line;

    while (!fin.eof()) {
        getline(fin, line);
        if (line[0] == '>') {
            latest = strip(line.substr(1, line.length()));
            records[latest] = "";
        } else {
            records[latest] += strip(line);
        }
    }

    return records;
}

/* Text */

Text::Text (string text, string foreground, string background, set<string> modes) {
    this -> text = text;
    this -> foreground = foreground;
    this -> modes = modes;
    render(text);
}

void Text::render (string text) {
    if (foreground != "" || background != "0" || modes.size() > 0) {
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
    } else {
        output = text;
    }
}

ostream& operator<< (ostream& output, const Text& text) {
    output << text.output;
    return output;
}

istream& operator>> (istream& input, Text& text) {
    string content;
    getline(input, content);
    text.render(content);
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

void Workspace::addLog (string type, Text* text) {
    logs.push_back(Log(
            type,
            text
        )
    );
}

void Workspace::showStrand (const Strand& strand, int indent, bool numbers, int length) const {
    string content = strand.getStrand();

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

void Workspace::showGenome (string id, string mode) const {
    Genome genome = *genomes.at(id);
    
    if (mode == "extended") {
        cout << Text("ID", "", "", {"dim", "bold"}) << endl;
        cout << "\t" << Text(id) << endl;
        cout << Text("RNA", "", "", {"dim", "bold"}) << endl;
        Workspace::showStrand(genome.getRNA(), 1, true);
        cout << Text("DNA", "", "", {"dim", "bold"}) << endl;
        cout << Text("\tFirst Strand", "", "", {"dim", "bold"}) << endl;
        Workspace::showStrand(genome.getDNA().first, 2, true);
        cout << Text("\tSecond Strand", "", "", {"dim", "bold"}) << endl;
        Workspace::showStrand(genome.getDNA().second, 2, true);
    } else if (mode == "compact") {
        cout << id << Text(" | ", "", "", {"dim"});
        showStrandSummary(genome.getRNA());
        cout << Text(" | ", "", "", {"dim"});
        showStrandSummary(genome.getDNA().first);
        cout << Text(" | ", "", "", {"dim"});
        showStrandSummary(genome.getDNA().second);
        cout << endl;
    }
}

void Workspace::showCell (string id, string mode) const {

}

void Workspace::showAnimal (string id, string mode) const {

}

void Workspace::showVirus (string id, string mode) const {

}

void Workspace::listGenomes () const {

}

void Workspace::listCells () const {

}

void Workspace::listAnimals () const {

}

void Workspace::listViruses () const {

}

/* Interface */

Interface::Interface (
    string name,
    string version,
    string datetime,
    string description,
    vector<string> authors
) {

}

void Interface::cleanInput () const {

}

void Interface::clearScreen () const {

}

bool Interface::askQuestion (const Text& message, string type) const {
    return true;
}

void Interface::showMessage (const Text& message, string type) const {

}

string Interface::getString (const Text& message) const {
    return "";
}

int Interface::getInteger (const Text& message) const {
    return 0;
}

map<string, string> Interface::getObject (const Text& title, string type, map<string, string> fields) const {
    return {};
}

void Interface::handleMenu (vector<string> choices, vector<void(*)()> functions) const {

}

void Interface::showWelcome () const {

}

void Interface::showAbout () const {

}

void Interface::showHelp (const Text& information) const {

}