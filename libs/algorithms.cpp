#include <iostream>
#include <vector>
#include "algorithms.h"

using namespace std;

/*
    Algorithm:
        Knuth-Morris-Pratt Pattern Searching Algorithm
    Description:
        There are two main parts inside this function:
            1. Computing LPS Table
            2. KMP Match
    Reference:
        https://www.scaler.com/topics/data-structures/kmp-algorithm/
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
    Algorithm:
        Pairwise [Global] Sequence Alignment Algorithm (Needleman-Wunsch Algorithm)
    Description:
        This is a customized minimal version of the algorithm.
    Reference:
        http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch
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

/*
    Algorithm:
        Dynamic Programming Approach
    Description:
        This function finds a longest common substring between two strings.
    References:
        https://www.scaler.com/topics/longest-common-substring/
        https://stackoverflow.com/a/30560066
*/
string findPairwiseLCS (string s1, string s2) {
    int n = s1.length();
    int m = s2.length();

    int mat[n + 1][m + 1];

    string lcs = "";

    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            if (i == 0 || j == 0) {
                mat[i][j] = 0;
            } else if (s1[i - 1] == s2[j - 1]) {
                mat[i][j] = mat[i - 1][j - 1] + 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (mat[i][j] > lcs.length()) {
                lcs = s1.substr(
                    i - mat[i][j],
                    mat[i][j]
                );
            }
        }
    }

    return lcs;
}

string findLCS (vector<string> strings) {
    while (strings.size() > 1) {
        for (int i = 0; i < strings.size() - 1; i++) {
            string s1 = strings.at(i);
            string s2 = strings.at(i + 1);

            string lcs = findPairwiseLCS(s1, s2);

            strings.insert(strings.begin() + i, lcs);

            strings.erase(
                strings.begin() + i + 1,
                strings.begin() + i + 2 + 1
            );
        }
    }
    return strings.at(0);
}