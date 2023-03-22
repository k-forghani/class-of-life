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

char Genome::getComplement (char n) const {
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
    string com = rna -> getStrand();

    for (int i = 0; i < com.length(); i++) {
        com[i] = Genome::getComplement(com[i]);
    }
    
    return make_pair<Strand, Strand>(
        Strand(rna -> getStrand()),
        Strand(com)
    );
}

void Genome::mutateSmallScaleRNA (char n1, char n2, int n) {
    n1 = toupper(n1);
    n2 = toupper(n2);
    
    string s = rna -> getStrand();

    int c = 0;

    for (int i = 0; i < s.length() && (n == -1 || c < n); i++) {
        if (s[i] == n1) {
            s[i] = n2;
            c++;
        }
    }

    rna -> setStrand(s);
}

void Genome::mutateSmallScaleDNA (char n1, char n2, int n) {
    n1 = toupper(n1);
    n2 = toupper(n2);

    string s1 = (dna -> first).getStrand();
    string s2 = (dna -> second).getStrand();
    
    int c = 0;

    for (int i = 0; i < s1.length() && (n == -1 || c < n); i++) {
        if (s1[i] == n1) {
            s1[i] = n2;
            s2[i] = Genome::getComplement(n2);
            c++;
        } else if (s2[i] == n1) {
            s2[i] = n2;
            s1[i] = Genome::getComplement(n2);
            c++;
        }
    }
    
    (dna -> first).setStrand(s1);
    (dna -> second).setStrand(s2);
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
