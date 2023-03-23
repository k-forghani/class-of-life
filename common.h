#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <set>

using namespace std;

const set<char> NUCLEOTIDES = {'A', 'C', 'G', 'T'};

char getComplement(char n);

#endif