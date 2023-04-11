#include <iostream>
#include "common.h"

using namespace std;

int randint (int lower, int upper) {
    return lower + rand() % (upper - lower + 1);
}

double randdbl (double lower, double upper, int precision) {
    return lower + (double)(rand() % (int)(precision * (upper - lower) + 1)) / precision;
}

string toupper (string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = toupper(text[i]);
    }
    return text;
}

string tolower (string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
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

string strip (string text) {
    while (isspace(*text.begin()))
        text.erase(0, 1);
    while (isspace(*(text.end() - 1)))
        text.erase(text.length() - 1, 1);
    return text;
}

string divide (string text, int length) {
    string ntext = "";
    
    for (int j = 0; j < text.length(); j++) {
        int segment = (j + 1) % length;
        if (segment == 0 || j == text.length() - 1) {
            if (segment == 0)
                segment = length;
            ntext += text.substr(j - segment + 1, segment);
        }
    }

    return ntext;
}

char getComplement (char n) {
    if (n == 'A')
        return 'T';
    else if (n == 'T')
        return 'A';
    else if (n == 'C')
        return 'G';
    else
        return 'C';
}

string getStrandComplement (string s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = getComplement(s[i]);
    return s;
}