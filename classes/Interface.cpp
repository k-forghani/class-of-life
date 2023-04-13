#include <iostream>
#include "../libs/common.h"
#include "Interface.h"

using namespace std;

/* Text */

/*
    The constructor of Text class
    Inputs:
        text : string (default: "")
            The plain text to be displayed
        foreground : string (default: "")
            The color of the text that can be selected from the following set:
            {black, red, green, yellow, blue, magenta, cyan, white, default}
        background : string (default: "")
            The background color of the text
        modes :  set<string> (default: {})
            A set containing enabled modes for the text that can be selected from the following set:
            {bold, dim, italic, underline, blinking, inverse, hidden, strikethrough}
*/
Text::Text (string text, string foreground, string background, set<string> modes) {
    this -> text = text;
    this -> foreground = foreground;
    this -> background = background;
    this -> modes = modes;
    render();
}

/*
    This private method renders the output.
*/
void Text::render () {
    if (foreground != "" || background != "" || modes.size() > 0) {
        #if __linux__
            output = ESCAPE + CONTROL;

            if (foreground != "")
                output += COLORS.at(foreground).first + SEPARATOR;

            if (background != "")
                output += COLORS.at(background).second + SEPARATOR;

            for (auto &&i : modes)
                output += MODES.at(i).first + SEPARATOR;
            
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

/*
    This method changes the text and renders the output.
    Inputs:
        text : string
            The new text to be displayed
*/
void Text::changeText (string text) {
    this -> text = text;
    Text::render();
}

/*
    This method changes the color of the text and renders the output.
    Inputs:
        foreground : string
            The new color of the text that can be selected from the following set:
            {black, red, green, yellow, blue, magenta, cyan, white, default}
*/
void Text::changeForeground (string foreground) {
    this -> foreground = foreground;
    Text::render();
}

/*
    This method changes the background color of the text and renders the output.
    Inputs:
        background:
            The new color of the text background can be selected from the following set:
            {black, red, green, yellow, blue, magenta, cyan, white, default}
*/
void Text::changeBackground (string background) {
    this -> background = background;
    Text::render();
}

/*
    This method changes the enabled modes for the text and renders the output.
    Inputs:
        modes:
            A set containing new enabled modes for the text that can be selected from the following set:
            {bold, dim, italic, underline, blinking, inverse, hidden, strikethrough}
*/
void Text::changeModes (set<string> modes) {
    this -> modes = modes;
    Text::render();
}

/*
    Overloded operator <<
*/
ostream& operator<< (ostream& output, const Text& text) {
    output << text.output;
    return output;
}

/*
    Overloded operator >>
*/
istream& operator>> (istream& input, Text& text) {
    string content;
    getline(input, content);
    text.changeText(content);
    return input;
}

/*
    Overloded operator +
*/
Text operator+ (const Text& t1, const Text& t2) {
    return Text(t1.output + t2.output);
}

/* Log */

/*
    The constructor of Log class
    Inputs:
        type : string
            The type of the log that can be selected from the following set:
            {INFO, WARNING, ERROR, SUCCESS}
        text : Text*
            A pointer to the Text object to be displayed
*/
Log::Log (string type, Text* text) {
    this -> type = toupper(type);
    this -> text = text;
}

/*
    This method prints the log.
    Inputs:
        type : bool
            The type of the log will be printed if true.
*/
void Log::print (bool type) const {
    if (type) {
        string color = COLORS.at(this -> type);
        cout << Text(this -> type, color) << " ";
    }
    cout << *text << endl;
}

/* Workspace */

/*
    The constructor of Workspace class
    Inputs:
        root : string
            The name of the workspace
*/
Workspace::Workspace (string root) {
    this -> root = root;
}

/*
    This method adds a log to the workspace.
    Inputs:
        type : string
            The type of the log that can be selected from the following set:
            {INFO, WARNING, ERROR, SUCCESS}
        text : Text*
            A pointer to the Text object to be displayed
        print : bool (default: true)
            The log will be printed if true.
*/
void Workspace::addLog (string type, Text* text, bool print) {
    Log log(type, text);
    logs.push_back(log);
    if (print)
        log.print();
}

/*
    This method prints a Strand object.
    Inputs:
        strand : Strand
            The Strand object that will be printed
        indent : int (default: 0)
            Indentation level
        numbers : bool (default: false)
            Line numbers will be shown if true
        length : int (default: 80)
            Maximum length of each line
*/
void Workspace::showStrand (const Strand& strand, int indent, bool numbers, int length) const {
    string content = strand.getStrand();

    if (content.length() <= length)
        numbers = false;

    int number = 1;

    for (int j = 0; j < content.length(); j++) {
        int segment = (j + 1) % length;
        if (segment == 0 || j == content.length() - 1) {
            if (segment == 0)
                segment = length;
            cout << string(indent, '\t');
            if (numbers)
                cout << Text(to_string(number), "", "", {"dim"}) << " ";
            cout << Text(content.substr(j - segment + 1, segment)) << endl;
            number++;
        }
    }
}

/*
    This method prints the summary of a Strand object.
    Inputs:
        strand : Strand
            The Strand object that will be printed
        length : int (default: 50)
            Maximum number of characters that will be shown
*/
void Workspace::showStrandSummary (const Strand& strand, int length) const {
    string content = strand.getStrand();

    if (content.length() == length)
        cout << Text(content);
    else if (content.length() > length)
        cout << Text(content.substr(0, length - 4) + " ...");
    else
        cout << Text(content) << string(length - content.length(), ' ');
}

/*
    This method prints a pair of Strand objects.
    Inputs:
        strands : pair<Strand, Strand>
            The pair of Strand objects that will be printed
        indent : int (default: 0)
            Indentation level
        numbers : bool (default: false)
            Line numbers will be shown if true
        length : int (default: 80)
            Maximum length of each line
*/
void Workspace::showPairOfStrands (const pair<Strand, Strand>& strands, int indent, bool numbers, int length) const {
    cout << string(indent, '\t') << Text("First Strand", "", "", {"dim", "bold"}) << endl;
    Workspace::showStrand(strands.first, indent + 1, numbers);
    cout << string(indent, '\t') << Text("Second Strand", "", "", {"dim", "bold"}) << endl;
    Workspace::showStrand(strands.second, indent + 1, numbers);
}

/*
    This method prints an item from the genomes list.
    Inputs:
        id : string
            The genome identifier
        mode : string
            The mode of display that can be selected from the following set:
            {extended, compact}
*/
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

/*
    This method prints a chromosome from cells or animals list.
    Inputs:
        from : string
            The type of the parent that cen be selected from the following set:
            {cell, animal}
        id : string
            The parent identifier
        index : int
            The index of the chromosome
        mode : string
            The mode of display that can be selected from the following set:
            {extended, compact}
*/
void Workspace::showChromosome (string from, string id, int index, string mode) const {
    vector<Chromosome*> chromosomes;
    if (from == "cell")
        chromosomes = cells.at(from) -> getChromosomes();
    else if (from == "animal")
        chromosomes = animals.at(from) -> getChromosomes();
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

/*
    This method prints an item from the cells list.
    Inputs:
        id : string
            The cell identifier
        mode : string
            The mode of display that can be selected from the following set:
            {extended, compact}
*/
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

/*
    This method prints an item from the animals list.
    Inputs:
        id : string
            The animal identifier
        mode : string
            The mode of display that can be selected from the following set:
            {extended, compact}
*/
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

/*
    This method prints an item from the viruses list.
    Inputs:
        id : string
            The cirus identifier
        mode : string
            The mode of display that can be selected from the following set:
            {extended, compact}
*/
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

/*
    This method prints the list of all genomes.
*/
void Workspace::listGenomes () const {
    for (auto &&i : genomes)
        Workspace::showGenome(i.first, "compact");
}

/*
    This method prints the list of all cells.
*/
void Workspace::listCells () const {
    for (auto &&i : cells)
        Workspace::showCell(i.first, "compact");
}

/*
    This method prints the list of all animals.
*/
void Workspace::listAnimals () const {
    for (auto &&i : animals)
        Workspace::showAnimal(i.first, "compact");
}

/*
    This method prints the list of all viruses.
*/
void Workspace::listViruses () const {
    for (auto &&i : viruses)
        Workspace::showVirus(i.first, "compact");
}

/* Interface */

/*
    The constructor of Interface class
    Inputs:
        name : string
            The name of the program
        version : string
            The version of the program
        datetime : string
            The release datetime of the program
        description : string
            A concise description for the program
        repository : string
            The address of the repository of the program
        authors : vector<string>
            A list of the developers of the program
*/
Interface::Interface (
    string name,
    string version,
    string datetime,
    string description,
    string repository,
    vector<string> authors
) : name(name), version(version), datetime(datetime), description(description), repository(repository), authors(authors) {}

/*
    This method cleans the input.
*/
void Interface::cleanInput () const {
    cin.clear();
    cin.ignore(10000, '\n');
}

/*
    This method clears the screen based on operating system.
*/
void Interface::clearScreen () const {
    #if __linux__
        system("clear");
    #elif _WIN32
        system("CLS");
    #else
        cout << "\033[L";
    #endif
}

/*
    This method handle a command.
    Inputs:
        command : string (default: "")
            The command to be parsed (gets from the input if empty)
    Output:
        blocks : vector<string>
            The blocks of the command after parsing
*/
vector<string> Interface::handleCommand (string command) const {
    cout << Text(">>>", "green", "", {"dim"}) << " ";
    if (command == "")
        getline(cin, command);
    else
        cout << Text(command, "", "", {"dim"}) << endl;
    vector<string> blocks;
    int previous = -1;
    bool quotation = false;
    for (int i = 0; i < command.length(); i++) {
        if (command[i] == ' ' && !quotation) {
            if (i - previous - 1 != 0)
                blocks.push_back(
                    command.substr(previous + 1, i - previous - 1)
                );
            previous = i;
        } else if (command[i] == '"' || command[i] == '\'') {
            if (quotation)
                if (i - previous - 1 != 0)
                    blocks.push_back(
                        command.substr(previous + 1, i - previous - 1)
                    );
            previous = i;
            quotation = !quotation;
        } else if (i == command.length() - 1) {
            if (i - previous != 0)
                blocks.push_back(
                    command.substr(previous + 1, i - previous)
                );
        }
    }
    return blocks;
}

/*
    This method shows the welcome section.
*/
void Interface::showWelcome () const {
    cout << Text(name) << " " << Text(version) << endl;
    cout << Text(description) << endl;
}

/*
    This method shows the about section.
*/
void Interface::showAbout () const {
    cout << Text("Name:       ", "", "", {"dim"}) << " " << Text(name) << endl;
    cout << Text("Version:    ", "", "", {"dim"}) << " " << Text(version) << endl;
    cout << Text("Rleased at: ", "", "", {"dim"}) << " " << Text(datetime) << endl;
    cout << Text("Description:", "", "", {"dim"}) << " " << Text(description) << endl;
    cout << Text("Developers: ", "", "", {"dim"}) << " ";
    for (int i = 0; i < authors.size(); i++) {
        cout << Text(authors.at(i));
        if (i < authors.size() - 1)
            cout << Text(", ");
    }
    cout << endl;
    cout << Text("Repository: ", "", "", {"dim"}) << " " << Text(repository) << endl;
}