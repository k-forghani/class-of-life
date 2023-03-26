#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <set>

using namespace std;

const set<char> NUCLEOTIDES = {'A', 'C', 'G', 'T'};
const double SIMILARITY_THRESHOLD = 0.7;

int randint(int lower, int upper);

double randdbl (double lower, double upper, int precision = 1000);

char getComplement(char n);

string getStrandComplement(string s);

int findPattern(string s, string p);

double getSimilarityScore(string s1, string s2);

#endif