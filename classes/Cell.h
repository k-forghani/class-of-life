#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Strand {
    private:
        string strand;
    
    public:
        Strand(string strand);
        void setStrand(string strand);
        string getStrand() const;
};

class Genome {
    protected:
        Strand* rna = new Strand("");
        pair<Strand, Strand>* dna = new pair<Strand, Strand>(Strand(""), Strand(""));
    
    public:
        Genome(string rna, string dnaf, string dnas);
        void setRNA(string s);
        void setDNA(string s1, string s2);
        Strand getRNA() const;
        pair<Strand, Strand> getDNA() const;
        pair<Strand, Strand> transformRNAtoDNA() const;
        void mutateSmallScaleRNA(char n1, char n2, int n = -1);
        void mutateSmallScaleDNA(char n1, char n2, int n = -1);
        void mutateLargeScaleRNA(string s1, string s2);
        void mutateLargeScaleDNA(string s1, string s2);
        void mutateInverselyRNA(string s);
        void mutateInverselyDNA(string s);
};

class Chromosome : public Genome {
    protected:
        Strand* rna = NULL;
    
    public:
        Chromosome(string s1, string s2);
        void setChromosome(string s1, string s2);
        pair<Strand, Strand> getChromosome() const;
        void mutateSmallScale(char n1, char n2, int n = -1);
        void mutateLargeScale(string s1, string s2);
        void mutateInversely(string s);
        bool isAbnormal() const;
};

class Cell {
    protected:
        int number;
        vector<Chromosome*> chromosomes;
    
    public:
        Cell(int n);
        ~Cell();
        void addChromosome(string s1, string s2);
        vector<Chromosome*> getChromosomes() const;
        void dieIfShould();
        void mutateSmallScale(char n1, char n2, int m, int n = -1);
        void mutateLargeScale(string s1, int n, string s2, int m);
        void mutateInversely(string s, int n);
        vector<vector<string>> getComplementaryPalindromes() const;
};

#endif