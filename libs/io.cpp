#include <iostream>
#include <fstream>
#include <map>
#include "common.h"
#include "io.h"

using namespace std;

/*
    This function reads and returns all lines of a file.
    Inputs:
        path : string
            The path of the file
    Output:
        lines : vector<string>
            The vector of the lines
*/
vector<string> readLines (string path) {
    ifstream fin(path);

    if (!fin.is_open())
        return {};

    vector<string> lines;

    string line;

    while (!fin.eof()) {
        getline(fin, line);
        lines.push_back(line);
    }

    return lines;
}

/*
    This function writes a map of sequence records into a FastA file.
    Inputs:
        recrods : map<string, string>
            The map of the sequence records which its keys are identifiers and its values are sequences
        path : string
            The path of the exported file
        length : int (default: 80)
            The maximum length of each line of the sequence
*/
void writeFastA (map<string, string> records, string path, int length) {
    ofstream fout(path);
    
    for (const auto &i : records)
        fout << ">" << strip(i.first) << "\n" << divide(i.second, length) << "\n";
    
    fout.close();
}

/*
    This function parses a FastA file and returns a map of its sequence records.
    Inputs:
        path : string
            The path of the file
    Output:
        recrods : map<string, string>
            The map of the sequence records which its keys are identifiers and its values are sequences
*/
map<string, string> parseFastA (string path) {
    map<string, string> records;

    string latest = "";

    vector<string> lines = readLines(path);

    for (auto &&line : lines) {
        if (line[0] == '>') {
            latest = strip(line.substr(1, line.length()));
            records[latest] = "";
        } else {
            records[latest] += strip(line);
        }
    }

    return records;
}