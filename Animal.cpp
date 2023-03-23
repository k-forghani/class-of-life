#include <iostream>
#include "Animal.h"

using namespace std;

/* Animal */

Animal::Animal (int n) : Cell(n) {

}

// NOTE: Not tested yet!
void Animal::killBadChromosomes () {
    auto i = chromosomes.begin();
    while (i != chromosomes.end()) {
        Chromosome c(**i);

        if (c.isAbnormal()) {
            i = chromosomes.erase(i);
        } else {
            ++i;
        }
    }
}

double Animal::getGeneticSimilarity (const Animal& animal) const {
    return 0.0;
}

Animal Animal::reproduceAsexually () const {
    return Animal(0);
}

bool operator== (const Animal& a1, const Animal& a2) {
    if (a1.number != a2.number) {
        return false;
    }

    if (a1.getGeneticSimilarity(a2) > 0.7) {
        return true;
    }

    return false;
}

Animal operator+ (const Animal& a1, const Animal& a2) {
    return Animal(0);
}

/* Virus */

Virus::Virus (string rna) : Genome(rna, "", "") {

}

void Virus::setVirus (string rna) {

}

Strand Virus::getVirus () const {
    return Strand("");
}

void Virus::mutateSmallScale (char n1, char n2, int m, int n) {

}

void Virus::mutateLargeScale (string s1, int n, string s2, int m) {

}

void Virus::mutateInversely (string s, int n) {

}

bool Virus::isPathogenic (const Animal& animal) const {
    return true;
}
