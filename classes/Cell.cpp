#include <iostream>
#include <vector>
#include "../libs/common.h"
#include "../libs/algorithms.h"
#include "Cell.h"

using namespace std;

/* Strand */

/*
    The constructor of Strand class
    Inputs:
        strand : string
            The content containing A, C, G, and T
*/
Strand::Strand (string strand) {
    Strand::setStrand(strand);
}

/*
    This method sets the content of the strand.
    Inputs:
        strand : string
            The content containing A, C, G, and T
*/
void Strand::setStrand (string strand) {
    this -> strand = "";
    for (int i = 0; i < strand.length(); i++) {
        char c = toupper(strand[i]);
        if (NUCLEOTIDES.count(c))
            this -> strand += c;
    }
}

/*
    This method returns the content of the strand.
    Output:
        strand : string
            The content of the strand
*/
string Strand::getStrand () const {
    return strand;
}

/* Genome */

/*
    The constructor of Genome class
    Inputs:
        rna : string
            The RNA strand
        dnaf : string
            The first strand of DNA
        dnas : string
            The second strand of DNA
*/
Genome::Genome (string rna, string dnaf, string dnas) {
    if (this -> rna != NULL)
        this -> rna -> setStrand(rna);
    if (this -> dna != NULL) {
        this -> dna -> first = Strand(dnaf);
        this -> dna -> second = Strand(dnas);
    }
}

/*
    This method sets the RNA strand of the genome if possible.
    Inputs:
        s : string
            The RNA strand
*/
void Genome::setRNA (string s) {
    if (rna != NULL)
        rna -> setStrand(s);
}

/*
    This method sets the DNA strands of the genome if possible.
    Inputs:
        s1 : string
            The first strand of DNA
        s2 : string
            The second strand of DNA
*/
void Genome::setDNA (string s1, string s2) {
    if (dna != NULL) {
        (dna -> first).setStrand(s1);
        (dna -> second).setStrand(s2);
    }
}

/*
    This method returns the Strand instance of RNA and an empty instance if doesn't exist.
    Output:
        rna : Strand
            The Strand instance of RNA
*/
Strand Genome::getRNA () const {
    if (rna != NULL)
        return *rna;
    else
        return Strand("");
}

/*
    This method returns a pair of DNA strands and a pair with empty instances if don't exist.
    Output:
        dna : pair<Strand, Strand>
            The pair of DNA strands
*/
pair<Strand, Strand> Genome::getDNA () const {
    if (dna != NULL)
        return *dna;
    else
        return make_pair(Strand(""), Strand(""));
}

/*
    This method make a DNA so that the first one is the RNA and the second one is its complement.
    Output:
        dna : pair<Strand, Strand>
            The pair of constructed DNA strands
*/
pair<Strand, Strand> Genome::transformRNAtoDNA () const {
    if (rna == NULL)
        return make_pair(Strand(""), Strand(""));

    string com = rna -> getStrand();

    for (int i = 0; i < com.length(); i++)
        com[i] = getComplement(com[i]);
    
    return make_pair<Strand, Strand>(
        Strand(rna -> getStrand()),
        Strand(com)
    );
}

/*
    This method mutates n first nucleotides n1 within RNA into nucleotides n2.
    Inputs:
        n1 : char
            The nucleotide which will be mutated
        n2 : char
            The nucleotide wich will be mutated into
        n : int (default: -1)
            Number of mutations (every occurrence will be mutated if -1)
*/
void Genome::mutateSmallScaleRNA (char n1, char n2, int n) {
    if (rna == NULL)
        return;

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

/*
    This method mutates n first nucleotides n1 within two strands of DNA into nucleotides n2.
    Inputs:
        n1 : char
            The nucleotide which will be mutated
        n2 : char
            The nucleotide wich will be mutated into
        n : int (default: -1)
            Number of mutations (every occurrence will be mutated if -1)
*/
void Genome::mutateSmallScaleDNA (char n1, char n2, int n) {
    if (dna == NULL)
        return;

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

/*
    This method mutates a chunk of nucleotides s1 within RNA into another chunk s2.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s1 : string
            The chunk of nucleotides which will be mutated
        s2 : string
            The chunk of nucleotides which will be mutated into
*/
void Genome::mutateLargeScaleRNA (string s1, string s2) {
    if (rna == NULL)
        return;

    s1 = Strand(s1).getStrand();
    s2 = Strand(s2).getStrand();
    
    string s = rna -> getStrand();

    int i = findPattern(s, s1);
    if (i > -1)
        s = s.replace(i, s1.length(), s2);

    rna -> setStrand(s);
}

/*
    This method mutates a chunk of nucleotides s1 within two strands of DNA into another chunk s2.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s1 : string
            The chunk of nucleotides which will be mutated
        s2 : string
            The chunk of nucleotides which will be mutated into
*/
void Genome::mutateLargeScaleDNA (string s1, string s2) {
    if (dna == NULL)
        return;

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

/*
    This method reverses a chunk of nucleotides within RNA.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s : string
            The chunk of nucleotides which will be reversed
*/
void Genome::mutateInverselyRNA (string s) {
    if (rna == NULL)
        return;

    string sr = "";
    for (int i = 0; i < s.length(); i++)
        sr = s[i] + sr;
    
    Genome::mutateLargeScaleRNA(s, sr);
}

/*
    This method reverses a chunk of nucleotides within two strands of DNA.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s : string
            The chunk of nucleotides which will be reversed
*/
void Genome::mutateInverselyDNA (string s) {
    if (dna == NULL)
        return;
    
    string sr = "";
    for (int i = 0; i < s.length(); i++)
        sr = s[i] + sr;
    
    Genome::mutateLargeScaleDNA(s, sr);
}

/* Chromosome */

/*
    The constructor of Chromosome class
    Inputs:
        s1 : string
            The first strand of DNA
        s2 : string
            The second strand of DNA
*/
Chromosome::Chromosome (string s1, string s2) : Genome("", s1, s2) {}

/*
    This method sets the content of DNA.
    Inputs:
        s1 : string
            The first strand of DNA
        s2 : string
            The second strand of DNA
*/
void Chromosome::setChromosome (string s1, string s2) {
    Chromosome::setDNA(s1, s2);
}

/*
    This method returns a pair of DNA strands and a pair with empty instances if don't exist.
    Output:
        dna : pair<Strand, Strand>
            The pair of DNA strands
*/
pair<Strand, Strand> Chromosome::getChromosome () const {
    return Chromosome::getDNA();
}

/*
    This method mutates n first nucleotides n1 within two strands of DNA into nucleotides n2.
    Inputs:
        n1 : char
            The nucleotide which will be mutated
        n2 : char
            The nucleotide wich will be mutated into
        n : int (default: -1)
            Number of mutations (every occurrence will be mutated if -1)
*/
void Chromosome::mutateSmallScale (char n1, char n2, int n) {
    Chromosome::mutateSmallScaleDNA(n1, n2, n);
}

/*
    This method mutates a chunk of nucleotides s1 within two strands of DNA into another chunk s2.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s1 : string
            The chunk of nucleotides which will be mutated
        s2 : string
            The chunk of nucleotides which will be mutated into
*/
void Chromosome::mutateLargeScale (string s1, string s2) {
    Chromosome::mutateLargeScaleDNA(s1, s2);
}

/*
    This method reverses a chunk of nucleotides within two strands of DNA.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s : string
            The chunk of nucleotides which will be reversed
*/
void Chromosome::mutateInversely (string s) {
    Chromosome::mutateInverselyDNA(s);
}

/*
    This methods checks if the genetic content of chromosome is abnormal.
    It returns true if there are more than 5 unbonded nucleotides or A-T bonds appear more than 3 times as often as G-C bonds.
    Output:
        abnormality : bool
            Abnormality state of chromosome based on the conditions mentioned before
*/
bool Chromosome::isAbnormal () const {
    string d1 = (dna -> first).getStrand();
    string d2 = (dna -> second).getStrand();

    int unbonded = 0;
    int at_bonds = 0;
    int gc_bonds = 0;

    for (int j = 0; j < d1.length(); j++) {
        if (d2[j] != getComplement(d1[j]))
            unbonded++;

        if ((d1[j] == 'A' && d2[j] == 'T') || (d1[j] == 'T' && d2[j] == 'A'))
            at_bonds++;

        if ((d1[j] == 'G' && d2[j] == 'C') || (d1[j] == 'C' && d2[j] == 'G'))
            at_bonds++;
    }
    
    if ((unbonded > 5) || ((double)at_bonds / (double)gc_bonds > 3))
        return true;

    return false;
}

/* Cell */

/*
    The constructor of Cell class
    Inputs:
        n : int
            Maximum number of chromosomes
*/
Cell::Cell (int n) {
    if (n > 0)
        number = n;
    else
        number = 1;
}

/*
    The destructor of Cell class
*/
Cell::~Cell () {
    for (auto i = chromosomes.begin(); i != chromosomes.end(); ++i)
        delete *i;
}

/*
    This method appends a chromosome to the cell.
    Inputs:
        s1 : string
            The first strand of DNA
        s2 : string
            The second strand of DNA
*/
void Cell::addChromosome (string s1, string s2) {
    if (chromosomes.size() < number)
        chromosomes.push_back(new Chromosome(s1, s2));
}

/*
    This method deletes a chromosome from the cell by its index.
    Inputs:
        index : int
            The index of the chromosome (starting from 0)
*/
void Cell::deleteChromosome (int index) {
    chromosomes.erase(chromosomes.begin() + index);
}

/*
    This method returns the list of pointers to chromosomes of the cell.
    Output:
        chromosomes : vector<Chromosome*>
            A vector containing pointers to the chromosomes of the cell
*/
vector<Chromosome*> Cell::getChromosomes () const {
    return chromosomes;
}

/*
    This method kills the cell and its chromosomes if there is one abnormal chromosome at least.
    Output:
        will_die : bool
            Will the cell die or not?
*/
bool Cell::dieIfShould () {
    for (auto &&i : chromosomes) {
        if (i -> isAbnormal()) {
            delete this;
            return true;
        }
    }

    return false;
}

/*
    This method mutates n first nucleotides n1 within chromosome m into nucleotides n2.
    Inputs:
        n1 : char
            The nucleotide which will be mutated
        n2 : char
            The nucleotide wich will be mutated into
        m : int
            The index of the chromosome (starting from 0)
        n : int (default: -1)
            Number of mutations (every occurrence will be mutated if -1)
*/
void Cell::mutateSmallScale (char n1, char n2, int m, int n) {
    chromosomes.at(m) -> mutateSmallScale(n1, n2, n);
}

/*
    This method swaps substring s1 within chromosome n and substring s2 within chromosome m.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s1 : string
            The substring within chromosome n
        n : int
            The index of first chromosome (starting from 0)
        s2 : string
            The substring within chromosome m
        m : int
            The index of second chromosome (starting from 0)
*/
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

/*
    This method reverses a chunk of nucleotides within chromosome n.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s : string
            The chunk of nucleotides which will be reversed
        m : int
            The index of the chromosome (starting from 0)
*/
void Cell::mutateInversely (string s, int n) {
    chromosomes.at(n) -> mutateInversely(s);
}

/*
    This method finds all complementary palindromes within all chromosomes of the cell.
    Algorithm:
        Innovative Semi-optimal Algorithm
    Output:
        palindromes : vector<vector<string>>
            a vector of all complementary palindromes that each item is a vector of the following form:
            {chromosome_index, strand_index, starting_index, ending_index, content}
*/
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
                    if (l - 1 < 0 || u + 1 > s.length() - 1)
                        break;
                }
            }

            dna.first = dna.second;
        }
    }

    return result;
}