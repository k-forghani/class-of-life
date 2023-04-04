#include <iostream>
#include "common.h"

using namespace std;

int randint (int lower, int upper) {
    return lower + rand() % (upper - lower + 1);
}

double randdbl (double lower, double upper, int precision) {
    return lower + (double)(rand() % (int)(precision * (upper - lower) + 1)) / precision;
}

vector<string> split (string text, char delimiter) {
    vector<string> items;

    int previous = 0;

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == delimiter) {
            items.push_back(
                text.substr(previous, i - previous)
            );
            previous = i + 1;
        } else if (i == text.length() - 1) {
            items.push_back(
                text.substr(previous, i - previous + 1)
            );
        }
    }
    
    return items;
}

char getComplement (char n) {
    if (n == 'A') {
        return 'T';
    } else if (n == 'T') {
        return 'A';
    } else if (n == 'C') {
        return 'G';
    } else {
        return 'C';
    }
}

string getStrandComplement (string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = getComplement(s[i]);
    }
    return s;
}