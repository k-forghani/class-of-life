#include <iostream>
#include <vector>
#include "algorithms.h"

using namespace std;

/*
    Algorithm:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Description:
        This function returns the index of first occurrence of a substring within a string.
        It has two main parts:
            1. Computing LPS Table
            2. KMP Match
    Inputs:
        s : string
            The string
        p : string
            The substring which will be searched for
    Output:
        index : int
            The index of the first occurrence (-1 if no occurrence was found)
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
            if (j == m)
                return i - j;
        } else if (i < n && p[j] != s[i]) {
            if (j > 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return -1;
}

/*
    Metric:
        Normalized Levenstein Distance
    Description:
        This is an implementation of normalized levenstein distance between two strings using iterative with full matrix approach.
    Approach:
        Dynamic Programming (Iterative with Full Matrix)
    Inputs:
        s1 : string
            First string
        s2 : string
            Second string
    Output:
        distance : double
            Normalized levenstein distance
    References:
        https://en.wikipedia.org/wiki/Levenshtein_distance
        https://devopedia.org/levenshtein-distance#qst-ans-3
*/
double computeNLD (string s1, string s2) {
    int match = 0;
    int mismatch = 1;
    int gap = 1;

    int n = s1.length();
    int m = s2.length();

    int mat[n + 1][m + 1];

    mat[0][0] = 0;
    
    for (int i = 1; i < n + 1; i++)
        mat[i][0] = i;
    
    for (int i = 1; i < m + 1; i++)
        mat[0][i] = i;

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            int cost;
            if (s1[i - 1] == s2[j - 1])
                cost = match;
            else
                cost = mismatch;
            mat[i][j] = min(
                min(
                    mat[i - 1][j] + gap,
                    mat[i][j - 1] + gap
                ),
                mat[i - 1][j - 1] + cost
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
            int minx = min(
                min(
                    mat[i - 1][j],
                    mat[i][j - 1]
                ),
                mat[i - 1][j - 1]
            );
            if (minx == mat[i - 1][j - 1]) {
                i--;
                j--;
            } else if (minx == mat[i - 1][j]) {
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
    Metric:
        Modified Hausdorff Similarity
    Description:
        This function computes a normalized similarity score between two sets of string pairs based on a modified version of Hausdorff distance.
        It uses normalized levenstein distance to compare a pair of strings.
    Inputs:
        a : vector<pair<string, string>>
            A vector of the string pairs of the first set
        b : vector<pair<string, string>>
            A vector of the string pairs of the second set
    Output:
        similarity : double
            Normalized similarity score
    References:
        https://en.wikipedia.org/wiki/Hausdorff_distance
*/
double computeMHS (vector<pair<string, string>> a, vector<pair<string, string>> b) {
    int n1 = a.size();
    int n2 = b.size();

    double distances[n1][n2];

    // Pairwise Distances

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            distances[i][j] = min(
                min(
                    computeNLD(a.at(i).first, b.at(j).first),
                    computeNLD(a.at(i).second, b.at(j).second)
                ),
                min(
                    computeNLD(a.at(i).first, b.at(j).second),
                    computeNLD(a.at(i).second, b.at(j).first)
                )
            );

    double s1 = 0;
    double s2 = 0;
    
    // 1st Summation

    for (int i = 0; i < n1; i++) {
        double min_dist = distances[i][0];
        for (int j = 1; j < n2; j++)
            if (distances[i][j] < min_dist)
                min_dist = distances[i][j];
        s1 += min_dist;
    }

    // 2nd Summation

    for (int j = 0; j < n2; j++) {
        double min_dist = distances[0][j];
        for (int i = 1; i < n1; i++)
            if (distances[i][j] < min_dist)
                min_dist = distances[i][j];
        s2 += min_dist;
    }
    
    // Modified Hausdorff Distance

    double dh = 0.5 * (s1 / n1 + s2 / n2);

    // Normalized Similarity Score

    return 1.0 - dh;
}

/*
    Description:
        This function finds a longest common substring (LCS) between two strings.
    Approach:
        Dynamic Programming
    Inputs:
        s1 : string
            First string
        s2 : string
            Second string
    Output:
        lcs : string
            A longest common substring (LCS)
    References:
        https://www.scaler.com/topics/longest-common-substring/
        https://stackoverflow.com/a/30560066
*/
string findPairwiseLCS (string s1, string s2) {
    int n = s1.length();
    int m = s2.length();

    int mat[n + 1][m + 1];

    string lcs = "";

    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < m + 1; j++)
            if (i == 0 || j == 0)
                mat[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                mat[i][j] = mat[i - 1][j - 1] + 1;
            else
                mat[i][j] = 0;

    for (int i = 1; i < n + 1; i++)
        for (int j = 1; j < m + 1; j++)
            if (mat[i][j] > lcs.length())
                lcs = s1.substr(
                    i - mat[i][j],
                    mat[i][j]
                );

    return lcs;
}

/*
    Description:
        This function finds a longest common substring (LCS) between several strings.
    Inputs:
        strings : vector<string>
            A vector containing several strings
    Output:
        lcs : string
            A longest common substring (LCS)
*/
string findLCS (vector<string> strings) {
    while (strings.size() > 1) {
        for (int i = 0; i < strings.size() - 1; i++) {
            string lcs = findPairwiseLCS(
                strings.at(i),
                strings.at(i + 1)
            );
            strings.insert(strings.begin() + i, lcs);
            strings.erase(
                strings.begin() + i + 1,
                strings.begin() + i + 2 + 1
            );
        }
    }
    return strings.at(0);
}