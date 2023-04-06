#include <iostream>
#include <set>
#include <vector>
#include "../libs/common.h"
#include "../libs/algorithms.h"
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
        if (NUCLEOTIDES.count(c)) {
            this -> strand += c;
        }
    }
}

string Strand::getStrand () const {
    return strand;
}

/* Genome */

Genome::Genome (string rna, string dnaf, string dnas) {
    if (this -> rna != NULL) {
        this -> rna -> setStrand(rna);
    }
    if (this -> dna != NULL) {
        this -> dna -> first = Strand(dnaf);
        this -> dna -> second = Strand(dnas);
    }
}

void Genome::setRNA (string s) {
    if (rna != NULL) {
        rna -> setStrand(s);
    }
}

void Genome::setDNA (string s1, string s2) {
    if (dna != NULL) {
        (dna -> first).setStrand(s1);
        (dna -> second).setStrand(s2);
    }
}

Strand Genome::getRNA () const {
    if (rna != NULL) {
        return *rna;
    } else {
        return Strand("");
    }
}

pair<Strand, Strand> Genome::getDNA () const {
    if (dna != NULL) {
        return *dna;
    } else {
        return make_pair(Strand(""), Strand(""));
    }
}

pair<Strand, Strand> Genome::transformRNAtoDNA () const {
    if (rna == NULL) {
        return make_pair(Strand(""), Strand(""));
    }

    string com = rna -> getStrand();

    for (int i = 0; i < com.length(); i++) {
        com[i] = getComplement(com[i]);
    }
    
    return make_pair<Strand, Strand>(
        Strand(rna -> getStrand()),
        Strand(com)
    );
}

void Genome::mutateSmallScaleRNA (char n1, char n2, int n) {
    if (rna == NULL) {
        return;
    }

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
    if (dna == NULL) {
        return;
    }

    n1 = toupper(n1);
    n2 = toupper(n2);

    string s1 = (dna -> first).getStrand();
    string s2 = (dna -> second).getStrand();
    
    int c = 0;

    for (int i = 0; i < s1.length() && (n == -1 || c < n); i++) {
        if (s1[i] == n1) {
            s1[i] = n2;
            s2[i] = getComplement(n2);
            c++;
        } else if (s2[i] == n1) {
            s2[i] = n2;
            s1[i] = getComplement(n2);
            c++;
        }
    }
    
    (dna -> first).setStrand(s1);
    (dna -> second).setStrand(s2);
}

void Genome::mutateLargeScaleRNA (string s1, string s2) {
    if (rna == NULL) {
        return;
    }

    s1 = Strand(s1).getStrand();
    s2 = Strand(s2).getStrand();
    
    string s = rna -> getStrand();

    int i = findPattern(s, s1);
    if (i > -1) {
        s = s.replace(i, s1.length(), s2);
    }

    rna -> setStrand(s);
}

void Genome::mutateLargeScaleDNA (string s1, string s2) {
    if (dna == NULL) {
        return;
    }

    s1 = Strand(s1).getStrand();
    s2 = Strand(s2).getStrand();

    string d1 = (dna -> first).getStrand();
    string d2 = (dna -> second).getStrand();

    int i = findPattern(d1, s1);
    int j = findPattern(d2, s1);
    
    if (i > -1 && (j == -1 || i <= j)) {
        d1 = d1.replace(i, s1.length(), s2);
        d2 = d2.replace(i, s1.length(), getStrandComplement(s2));
    } else if (j > -1) {
        d2 = d2.replace(j, s1.length(), s2);
        d1 = d1.replace(j, s1.length(), getStrandComplement(s2));
    }
    
    (dna -> first).setStrand(d1);
    (dna -> second).setStrand(d2);
}

void Genome::mutateInverselyRNA (string s) {
    if (rna == NULL) {
        return;
    }

    string sr = "";
    for (int i = 0; i < s.length(); i++) {
        sr = s[i] + sr;
    }
    
    Genome::mutateLargeScaleRNA(s, sr);
}

void Genome::mutateInverselyDNA (string s) {
    if (dna == NULL) {
        return;
    }
    
    string sr = "";
    for (int i = 0; i < s.length(); i++) {
        sr = s[i] + sr;
    }
    
    Genome::mutateLargeScaleDNA(s, sr);
}

void Genome::printRNA (string before) const {
    cout << before << Genome::getRNA().getStrand() << endl;
}

void Genome::printDNA (string before) const {
    cout << before << Genome::getDNA().first.getStrand() << endl << Genome::getDNA().second.getStrand() << endl;
}

/* Chromosome */

Chromosome::Chromosome (string s1, string s2) : Genome("", s1, s2) {}

void Chromosome::setChromosome (string s1, string s2) {
    Chromosome::setDNA(s1, s2);
}

pair<Strand, Strand> Chromosome::getChromosome () const {
    return Chromosome::getDNA();
}

void Chromosome::mutateSmallScale (char n1, char n2, int n) {
    Chromosome::mutateSmallScaleDNA(n1, n2, n);
}

void Chromosome::mutateLargeScale (string s1, string s2) {
    Chromosome::mutateLargeScaleDNA(s1, s2);
}

void Chromosome::mutateInversely (string s) {
    Chromosome::mutateInverselyDNA(s);
}

bool Chromosome::isAbnormal () const {
    string d1 = (dna -> first).getStrand();
    string d2 = (dna -> second).getStrand();

    int unbonded = 0;
    int at_bonds = 0;
    int gc_bonds = 0;

    for (int j = 0; j < d1.length(); j++) {
        if (d2[j] != getComplement(d1[j])) {
            unbonded++;
        }

        if ((d1[j] == 'A' && d2[j] == 'T') || (d1[j] == 'T' && d2[j] == 'A')) {
            at_bonds++;
        }

        if ((d1[j] == 'G' && d2[j] == 'C') || (d1[j] == 'C' && d2[j] == 'G')) {
            at_bonds++;
        }
    }
    
    if ((unbonded > 5) || ((double)at_bonds / (double)gc_bonds > 3)) {
        return true;
    }

    return false;
}

void Chromosome::print (string before) const {
    Chromosome::printDNA(before);
}

/* Cell */

Cell::Cell (int n) {
    if (n > 0) {
        number = n;
    } else {
        number = 1;
    }
}

Cell::~Cell () {
    for (auto i = chromosomes.begin(); i != chromosomes.end(); ++i) {
        delete *i;
    }
}

void Cell::addChromosome (string s1, string s2) {
    if (chromosomes.size() < number) {
        chromosomes.push_back(new Chromosome(s1, s2));
    }
}

vector<Chromosome*> Cell::getChromosomes () const {
    return chromosomes;
}

void Cell::dieIfShould () {
    bool will_die = false;

    for (auto i = chromosomes.begin(); i != chromosomes.end(); ++i) {
        Chromosome c(**i);

        if (c.isAbnormal()) {
            will_die = true;
            break;
        }
    }
    
    // NOTE: Object must be constructed using 'new' keyword.
    if (will_die) {
        delete this;
    }
}

void Cell::mutateSmallScale (char n1, char n2, int m, int n) {
    Chromosome* c(chromosomes.at(m));
    c -> mutateSmallScale(n1, n2, n);
}

void Cell::mutateLargeScale (string s1, int n, string s2, int m) {
    s1 = Strand(s1).getStrand();
    s2 = Strand(s2).getStrand();

    Chromosome* cn(chromosomes.at(n));
    Chromosome* cm(chromosomes.at(m));
    
    int cni = findPattern((cn -> getChromosome()).first.getStrand(), s1);
    int cnj = findPattern((cn -> getChromosome()).second.getStrand(), s1);
    int cmi = findPattern((cm -> getChromosome()).first.getStrand(), s2);
    int cmj = findPattern((cm -> getChromosome()).second.getStrand(), s2);

    if ((cni > -1 || cnj > -1) && (cmi > -1 || cmj > -1)) { 
        cn -> mutateLargeScale(s1, s2);
        cm -> mutateLargeScale(s2, s1);
    }
}

void Cell::mutateInversely (string s, int n) {
    Chromosome* c(chromosomes.at(n));
    c -> mutateInversely(s);
}

vector<vector<string>> Cell::getComplementaryPalindromes () const {
    vector<vector<string>> result;

    for (auto i = chromosomes.begin(); i != chromosomes.end(); ++i) {
        int chromosome_index = i - chromosomes.begin() + 1;

        pair<Strand, Strand> dna = (**i).getChromosome();
        string s = dna.first.getStrand();

        for (int j = 0; j < 2; j++) {
            int strand_index = j + 1;
            
            s = dna.first.getStrand();

            for (int k = 0; k < s.length() - 1; k++) {
                for (int q = 0; q < s.length() / 2 - 1; q++) {
                    int l = k - q;
                    int u = k + 1 + q;
                    if (s[l] == getComplement(s[u])) {
                        result.push_back(
                            {
                                to_string(chromosome_index),
                                to_string(strand_index),
                                to_string(l),
                                to_string(u),
                                s.substr(l, u - l + 1)
                            }
                        );
                    } else {
                        break;
                    }
                    if (l - 1 < 0 || u + 1 > s.length() - 1) {
                        break;
                    }
                }
            }

            dna.first = dna.second;
        }
    }

    return result;
}