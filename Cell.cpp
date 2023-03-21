#include <iostream>
#include <set>
#include "Cell.h"

using namespace std;

/* Strand */

void Strand::normalize () {
    string nstrand = "";

    for (int i = 0; i < strand.length(); i++) {
        char c = toupper(strand[i]);
        if (nucleotides.count(c))
            nstrand += c;
    }

    strand = nstrand;
}

bool Strand::validate () const {
    return true;
}

Strand::Strand (string strand) {
    Strand::setStrand(strand);
}

void Strand::setStrand (string strand) {
    this -> strand = strand;
    normalize();
}

string Strand::getStrand () const {
    return strand;
}

/* Genome */

Genome::Genome (string rna, string dnaf, string dnas) {

}

void Genome::setRNA (string s) {

}

void Genome::setDNA (string s1, string s2) {

}

Strand* Genome::getRNA () const {

}

pair<Strand*, Strand*> Genome::getDNA () const {

}

pair<Strand*, Strand*> Genome::transformRNAtoDNA () const {

}

void Genome::mutateSmallScaleRNA (char n1, char n2, int n) {

}

void Genome::mutateSmallScaleDNA (char n1, char n2, int n) {

}

void Genome::mutateLargeScaleRNA (string s1, string s2) {

}

void Genome::mutateLargeScaleDNA (string s1, string s2) {

}

void Genome::mutateInverselyRNA (string s) {

}

void Genome::mutateInverselyDNA (string s) {

}

/* Chromosome */

Chromosome::Chromosome (string s1, string s2) : Genome("", s1, s2) {

}

void Chromosome::setChromosome (string s1, string s2) {

}

pair<Strand*, Strand*> Chromosome::getChromosome () const {

}

void Chromosome::mutateSmallScale (char n1, char n2, int n) {

}

void Chromosome::mutateLargeScale (string s1, string s2) {

}

void Chromosome::mutateInversely (string s) {

}

/* Cell */

Cell::Cell (int n) {

}

void Cell::addChromosome (const Chromosome& c) {

}

void Cell::dieIfShould () {

}

void Cell::mutateSmallScale (char n1, char n2, int m, int n) {

}

void Cell::mutateLargeScale (string s1, int n, string s2, int m) {

}

void Cell::mutateInversely (string s, int n) {

}

void Cell::printComplementaryPalindromes () const {

}
