#include <iostream>
#include <utility>
#include <set>
#include "Cell.h"

using namespace std;

/* Strand */

Strand::Strand (string strand) {
    Strand::setStrand(strand);
}

void Strand::setStrand (string strand) { 
    this -> strand = "";

    for (int i = 0; i < strand.length(); i++) {
        char c = toupper(strand[i]);
        if (nucleotides.count(c))
            this -> strand += c;
    }
}

string Strand::getStrand () const {
    return strand;
}

/* Genome */

Genome::Genome (string rna, string dnaf, string dnas) {
    this -> rna = new Strand(rna);
    this -> dna = new pair<Strand, Strand>(Strand(dnaf), Strand(dnas));
}

void Genome::setRNA (string s) {
    rna -> setStrand(s);
}

void Genome::setDNA (string s1, string s2) {
    (dna -> first).setStrand(s1);
    (dna -> second).setStrand(s2);
}

Strand Genome::getRNA () const {
    return *rna;
}

pair<Strand, Strand> Genome::getDNA () const {
    return *dna;
}

pair<Strand, Strand> Genome::transformRNAtoDNA () const {
    string comp = rna -> getStrand();

    for (int i = 0; i < comp.length(); i++) {
        if (comp[i] == 'A') {
            comp[i] = 'T';
        } else if (comp[i] == 'T') {
            comp[i] = 'A';
        } else if (comp[i] == 'C') {
            comp[i] = 'G';
        } else {
            comp[i] = 'C';
        }
    }
    
    return make_pair<Strand, Strand>(
        Strand(rna -> getStrand()),
        Strand(comp)
    );
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

pair<Strand, Strand> Chromosome::getChromosome () const {

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
