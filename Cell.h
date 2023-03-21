#include <iostream>
#include <utility>

using namespace std;

class Strand {
    private:
        string strand;
        void normalize();
        bool validate();
    
    public:
        Strand(string strand);
        void set(string strand);
        string get();
};

class Genome {
    protected:
        Strand* rna;
        pair<Strand*, Strand*> dna;
    
    public:
        Genome(string rna, string dnaf, string dnas);
        void setRNA(string s);
        void setDNA(string s1, string s2);
        Strand* getRNA();
        pair<Strand*, Strand*> getDNA();
        pair<Strand*, Strand*> transformRNAtoDNA();
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
        void set(string s1, string s2);
        pair<Strand*, Strand*> get();
        void mutateSmallScale(char n1, char n2, int n = -1);
        void mutateLargeScale(string s1, string s2);
        void mutateInversely(string s);
};

class Cell {
    protected:
        int number;
        Chromosome* chromosome;
    
    public:
        Cell(int n);
        void addChromosome(const Chromosome& c);
        void dieIfShould();
        void mutateSmallScale(char n1, char n2, int m, int n = -1);
        void mutateLargeScale(string s1, int n, string s2, int m);
        void mutateInversely(string s, int n);
        void printComplementaryPalindromes();
};