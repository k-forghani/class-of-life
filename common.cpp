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

// Knuth-Morris-Pratt Pattern Searching (Computing LPS Table + KMP Match)
// Find more at https://www.scaler.com/topics/data-structures/kmp-algorithm/.
int findPattern (string s, string p) {
    // Computing LPS Table
    
    int m = p.length();

    int lps[m];
    lps[0] = 0;

    int len = 0; // length of previous longest proper prefix that is also a suffix
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
        if (s[i] == p[j]) { // the characters are a match
            i++;
            j++;
            if (j == m) { // j pointer has reached end of pattern
                return i - j; // index of the match
            }
        } else if (i < n && p[j] != s[i]) { // no match
            if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return -1; // no match
}