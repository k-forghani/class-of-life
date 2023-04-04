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

Text::Text (string text, string foreground, string background, set<string> modes) {
    this -> text = text;
    this -> foreground = foreground;
    this -> modes = modes;
    
    render();
}

void Text::render () {
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

void Text::change (string text) {
    this -> text = text;
    render();
}

ostream& operator<< (ostream& output, const Text& text) {
    output << text.output;
    return output;
}

istream& operator>> (istream& input, Text& text) {
    string content;
    getline(input, content);
    text.change(content);
    return input;
}

Text operator+ (const Text& t1, const Text& t2) {
    return Text(t1.output + t2.output);
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
