#include <iostream>
#include "Animal.h"

using namespace std;

/* Animal */

Animal::Animal (int n) : Cell(n) {

}

void Animal::killBadChromosomes () {

}

double Animal::getGeneticSimilarity (const Animal& animal) const {

}

Animal* Animal::reproduceAsexually () const {

}

bool operator== (const Animal& a1, const Animal& a2) {

}

Animal* operator+ (const Animal& a1, const Animal& a2) {

}

/* Virus */

Virus::Virus (string rna) : Genome(rna, "", "") {

}

void Virus::set (string rna) {

}

Strand* Virus::get () const {

}

void Virus::mutateSmallScale (char n1, char n2, int m, int n = -1) {

}

void Virus::mutateLargeScale (string s1, int n, string s2, int m) {

}

void Virus::mutateInversely (string s, int n) {

}

bool Virus::isPathogenic (const Animal& animal) const {

}
