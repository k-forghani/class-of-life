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
        string seq = strip(i.second);
        string nseq = "";
        
        for (int j = 0; j < seq.length(); j++) {
            if ((j + 1) % length == 0 || j == seq.length() - 1) {
                int segment = (j + 1) % length;
                nseq += seq.substr(j - segment + 1, segment);
            }
        }
        
        fout << ">" << id << "\n" << nseq << "\n";
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
