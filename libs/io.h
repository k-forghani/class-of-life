#ifndef IO_H
#define IO_H

#include <iostream>
#include <map>

using namespace std;

vector<string> readLines (string path);

void writeFastA(map<string, string> records, string path, int length = 80);

map<string, string> parseFastA(string path);

#endif