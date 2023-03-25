#include <iostream>
#include "common.h"

using namespace std;

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

/*
    Knuth-Morris-Pratt Pattern Searching Algorithm
    Description: There are two main parts inside this function:
        1. Computing LPS Table
        2. KMP Match
    Reference: https://www.scaler.com/topics/data-structures/kmp-algorithm/
*/
int findPattern (string s, string p) {
    // Computing LPS Table
    
    int m = p.length();

    int lps[m];
    lps[0] = 0;

    int len = 0;
    int i = 1;

    while (i < m) {
        if (p[i] == p[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    // KMP Match

    i = 0;
    int j = 0;
    int n = s.length();

    while (i < n) {
        if (s[i] == p[j]) {
            i++;
            j++;
            if (j == m) {
                return i - j;
            }
        } else if (i < n && p[j] != s[i]) {
            if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return -1;
}