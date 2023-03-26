#include <iostream>
#include <vector>
#include "common.h"

using namespace std;

int randint (int lower, int upper) {
    return lower + rand() % (upper - lower + 1);
}

double randdbl (double lower, double upper, int precision) {
    return lower + (double)(rand() % (int)(precision * (upper - lower) + 1)) / precision;
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

/*
    Algorithm: Pairwise [Global] Sequence Alignment Algorithm (Needleman-Wunsch Algorithm)
    Description: This is a customized minimal version of the algorithm.
    Reference: http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch
*/
double getSimilarityScore (string s1, string s2) {
    int match = 1;
    int mismatch = 0;
    int gap = 0;

    int n = s1.length();
    int m = s2.length();

    int mat[n + 1][m + 1];

    mat[0][0] = 0;
    
    for (int i = 1; i < n + 1; i++) {
        mat[i][0] = mat[i - 1][0] + gap;
    }
    
    for (int i = 1; i < m + 1; i++) {
        mat[0][i] = mat[0][i - 1] + gap;
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            int score = mismatch;
            if (s1[i - 1] == s2[j - 1]) {
                score = match;
            }
            mat[i][j] = max(
                max(
                    mat[i - 1][j] + gap,
                    mat[i][j - 1] + gap
                ),
                mat[i - 1][j - 1] + score
            );
        }
    }

    int i = n;
    int j = m;
    int length = 0;

    while (i != 0 || j != 0) {
        if (i == 0) {
            j--;
        } else if (j == 0) {
            i--;
        } else {
            int maxx = max(
                max(
                    mat[i - 1][j],
                    mat[i][j - 1]
                ),
                mat[i - 1][j - 1]
            );
            if (maxx == mat[i - 1][j - 1]) {
                i--;
                j--;
            } else if (maxx == mat[i - 1][j]) {
                i--;
            } else {
                j--;
            }
        }
        length++;
    }

    return (double)mat[n][m] / (double)length;
}

string findLCS (vector<string> strings) {
    return "";
}