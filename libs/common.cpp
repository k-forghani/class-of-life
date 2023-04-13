#include <iostream>
#include <vector>
#include "common.h"

using namespace std;

/*
    This function returns an integer number within interval [lower, upper].
    Inputs:
        lower : int
            Lower boundary
        upper : int
            Upper boundary
    Output:
        number : int
            Generated random number
*/
int randint (int lower, int upper) {
    return lower + rand() % (upper - lower + 1);
}

/*
    This function makes all characters of a string uppercase.
    Inputs:
        text : string
            The target string
    Output:
        text : string
            The uppercase string
*/
string toupper (string text) {
    for (int i = 0; i < text.length(); i++)
        text[i] = toupper(text[i]);
    return text;
}

/*
    This function makes all characters of a string lowercase.
    Inputs:
        text : string
            The target string
    Output:
        text : string
            The lowercase string
*/
string tolower (string text) {
    for (int i = 0; i < text.length(); i++)
        text[i] = tolower(text[i]);
    return text;
}

/*
    This function splits a string by a specific delimiter and returns the items.
    Inputs:
        text : string
            The target string
        delimiter : char (default: ' ')
            The delimiter
    Output:
        items : vector<string>
            A vector of the items
*/
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

/*
    This function removes whitespaces from the left and the right of a string.
    Inputs:
        text : string
            The target string
    Output:
        text : string
            The cleaned string
*/
string strip (string text) {
    while (isspace(*text.begin()))
        text.erase(0, 1);
    while (isspace(*(text.end() - 1)))
        text.erase(text.length() - 1, 1);
    return text;
}

/*
    This function divides a string into segments with a fixed length.
    Inputs:
        text : string
            The target string
        length : int (default: 80)
            The length of the segments
    Output:
        ntext : string
            The segmented string
*/
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

/*
    This function returns the complement of a nucleotide.
    Inputs:
        n : char
            The target nucleotide
    Output:
        c : char
            The complementary nucleotide
*/
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

/*
    This function returns the complement of a sequence containing nucleotides.
    Inputs:
        s : string
            The target sequence
    Output:
        c : string
            The complementary sequence
*/
string getStrandComplement (string s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = getComplement(s[i]);
    return s;
}