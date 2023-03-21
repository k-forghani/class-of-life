#include <iostream>
#include <utility>
#include "Cell.h"

using namespace std;

class Animal : public Cell {
    public:
        Animal(int n);
        void killBadChromosomes();
        double getGeneticSimilarity(const Animal& animal) const;
        Animal* reproduceAsexually() const;
        
        friend bool operator==(const Animal& a1, const Animal& a2);
        friend Animal* operator+(const Animal& a1, const Animal& a2);

        friend class Virus;
};

class Virus : public Genome {
    protected:
        pair<Strand*, Strand*> dna = make_pair<Strand*, Strand*>(NULL, NULL);

    public:
        Virus(string rna);
        void set(string rna);
        Strand* get() const;
        void mutateSmallScale(char n1, char n2, int m, int n = -1);
        void mutateLargeScale(string s1, int n, string s2, int m);
        void mutateInversely(string s, int n);
        bool isPathogenic(const Animal& animal) const;
};