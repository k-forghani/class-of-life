#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
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
        pair<Strand, Strand>* dna = NULL;

    public:
        Virus(string rna);
        void setVirus(string rna);
        Strand getVirus() const;
        void mutateSmallScale(char n1, char n2, int n = -1);
        void mutateLargeScale(string s1, string s2);
        void mutateInversely(string s);
        bool isPathogenic(const Animal& animal) const;
};

#endif