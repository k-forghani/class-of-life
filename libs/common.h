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

vector<string> split(string text, char delimiter = ' ');

char getComplement(char n);

string getStrandComplement(string s);

#endif