#include <iostream>
#include "Animal.h"

using namespace std;

/* Animal */

Animal::Animal (int n) : Cell(n) {

}

void Animal::killBadChromosomes () {

}

double Animal::getGeneticSimilarity (const Animal& animal) const {
    return 0.0;
}

Animal Animal::reproduceAsexually () const {
    return Animal(0);
}

bool operator== (const Animal& a1, const Animal& a2) {
    return true;
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
