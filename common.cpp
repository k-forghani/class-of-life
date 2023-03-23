#include <iostream>
#include <set>
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