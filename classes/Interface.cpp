#include <iostream>
#include <fstream>
#include "Interface.h"

using namespace std;

/* FastA */

FastA::FastA (string path) {
    this -> path = path;
}

void FastA::write (map<string, string> content, int length) const {
    ofstream fout(path);
    
    for (const auto &i : content) {
        string id = i.first;
        string seq = "";
        
        for (int j = 0; j < i.second.length(); j++) {
            if ((j + 1) % length == 0 || j == i.second.length() - 1) {
                int segment = (j + 1) % length;
                seq += i.second.substr(j - segment + 1, segment);
            }
        }
        
        fout << ">" << id << "\n" << seq << "\n";
    }
    
    fout.close();
}

map<string, string> FastA::parse () const {
    ifstream fin(path);

    if (!fin.is_open()) {
        return {};
    }

    string line;

    map<string, string> content;

    string latest = "";

    while (!fin.eof()) {
        getline(fin, line);
        if (line[0] == '>') {
            latest = line.substr(1, line.length() - 1);
            content[latest] = "";
        } else {
            content[latest] += line.substr(0, line.length());
        }
    }

    return content;
}

/* Text */

Text::Text(string text, string foreground, string background, set<string> modes) {

}

ostream& operator<< (ostream& output, const Text& text) {

}

istream& operator>> (istream& input, const Text& text) {

}

Text operator+ (const Text& t1, const Text& t2) {

}

/* Log */

Log::Log (string type, const Text& text) {

}

void Log::print(bool type) const {

}

/* Logger */

Logger::Logger (string root, bool type) {

}

void Logger::log (string type, Text text, bool print) const {

}

/* Workspace */

/* Interface */
