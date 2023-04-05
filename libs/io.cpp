#include <iostream>
#include <fstream>
#include <map>
#include "common.h"
#include "io.h"

using namespace std;

void writeFastA (map<string, string> records, string path, int length) {
    ofstream fout(path);
    
    for (const auto &i : records) {
        string id = strip(i.first);
        string seq = divide(i.second, length);
        fout << ">" << id << "\n" << seq << "\n";
    }
    
    fout.close();
}

map<string, string> parseFastA (string path) {
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