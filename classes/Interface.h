#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "Cell.h"
#include "Animal.h"

using namespace std;

class Text {
    private:
        // Reference: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
        const string ESCAPE = "\033";
        const string CONTROL = "[";
        const string SEPARATOR = ";";
        const string END = "m";
        const map<string, pair<string, string>> COLORS = {
            {"black",   {"30", "40"}},
            {"red",     {"31", "41"}},
            {"green",   {"32", "42"}},
            {"yellow",  {"33", "43"}},
            {"blue",    {"34", "44"}},
            {"magenta", {"35", "45"}},
            {"cyan",    {"36", "46"}},
            {"white",   {"37", "47"}},
            {"default", {"39", "49"}},
        };
        const map<string, pair<string, string>> MODES {
            {"bold",          {"1", "22"}},
            {"dim",           {"2", "22"}},
            {"italic",        {"3", "23"}},
            {"underline",     {"4", "24"}},
            {"blinking",      {"5", "25"}},
            {"inverse",       {"7", "27"}},
            {"hidden",        {"8", "28"}},
            {"strikethrough", {"9", "29"}},
        };
        const string RESET = "0";
        
        string text;
        string foreground;
        string background;
        set<string> modes;
        string output;
        
    public:
        Text(
            string text = "",
            string foreground = "",
            string background = "",
            set<string> modes = {}
        );

        void render(string text);
        
        friend ostream& operator<<(ostream& output, const Text& text);
        friend istream& operator>>(istream& input, Text& text);
        friend Text operator+(const Text& t1, const Text& t2);
};

class Log {
    private:
        const map<string, string> COLORS = {
            {"INFO", "cyan"},
            {"WARNING", "yellow"},
            {"ERROR", "red"},
            {"SUCCESS", "green"}
        };

        string type;
        Text* text;
    
    public:
        Log(string type, Text* text);
        void print(bool type) const;
};

class Workspace {
    private:
        string root;
        vector<Log> logs;
    
    public:
        map<string, Genome*> genomes;
        map<string, Cell*> cells;
        map<string, Animal*> animals;
        map<string, Virus*> viruses;

        Workspace(string root = "");

        void addLog(string type, Text* text);

        void showStrand(const Strand& strand, int indent = 0, bool numbers = false, int length = 80) const;
        void showStrandSummary (const Strand& strand, int length = 50) const;
        void showGenome(string id, string mode) const;
        void showCell(string id, string mode) const;
        void showAnimal(string id, string mode) const;
        void showVirus(string id, string mode) const;
        
        void listGenomes() const;
        void listCells() const;
        void listAnimals() const;
        void listViruses() const;
};

class Interface {
    private:
        string name;
        string version;
        string datetime;
        string description;
        vector<string> authors;
    
    public:
        Interface(
            string name,
            string version,
            string datetime,
            string description,
            vector<string> authors
        );

        void cleanInput() const;
        void clearScreen() const;

        bool askQuestion(const Text& message, string type) const;
        void showMessage(const Text& message, string type) const;

        string getString(const Text& message) const;
        int getInteger(const Text& message) const;
        map<string, string> getObject(const Text& title, string type, map<string, string> fields) const;
        
        void handleMenu(vector<string> choices, vector<void(*)()> functions) const;

        void showWelcome() const;
        void showAbout() const;
        void showHelp(const Text& information) const;
};

#endif