#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <set>

using namespace std;

/* Common Constants */

const set<char> NUCLEOTIDES = {'A', 'C', 'G', 'T'};
const double SIMILARITY_THRESHOLD = 0.7;

/* Common Functions */

int randint(int lower, int upper);

double randdbl(double lower, double upper, int precision = 1000);

string toupper(string text);

string tolower(string text);

vector<string> split(string text, char delimiter = ' ');

string strip(string text);

string divide(string text, int length = 80);

char getComplement(char n);

string getStrandComplement(string s);

#endif