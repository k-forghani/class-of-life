#include <iostream>
#include "common.h"
#include "Animal.h"

using namespace std;

/* Animal */

Animal::Animal (int n) : Cell(n) {}

void Animal::killBadChromosomes () {
    auto i = chromosomes.begin();
    while (i != chromosomes.end()) {
        Chromosome c(**i);

        if (c.isAbnormal()) {
            i = chromosomes.erase(i);
        } else {
            ++i;
        }
    }
    number = chromosomes.size();
}

double Animal::getGeneticSimilarity (const Animal& animal) const {
    string g1s1 = "";
    string g1s2 = "";
    string g2s1 = "";
    string g2s2 = "";

    for (auto i = chromosomes.begin(); i != chromosomes.end(); ++i) {
        pair<Strand, Strand> dna = (**i).getChromosome();
        g1s1 += dna.first.getStrand();
        g1s2 += dna.second.getStrand();
    }
    
    for (auto i = animal.chromosomes.begin(); i != animal.chromosomes.end(); ++i) {
        pair<Strand, Strand> dna = (**i).getChromosome();
        g2s1 += dna.first.getStrand();
        g2s2 += dna.second.getStrand();
    }

    return max(
        max(
            getSimilarityScore(g1s1 + g1s2, g2s1 + g2s2),
            getSimilarityScore(g1s1 + g1s2, g2s2 + g2s1)
        ),
        max(
            getSimilarityScore(g1s2 + g1s1, g2s1 + g2s2),
            getSimilarityScore(g1s2 + g1s1, g2s2 + g2s1)
        )
    );
}

Animal Animal::reproduceAsexually () const {
    return Animal(0);
}

bool operator== (const Animal& a1, const Animal& a2) {
    if (a1.number != a2.number) {
        return false;
    }

    if (a1.getGeneticSimilarity(a2) > 0.7) {
        return true;
    }

    return false;
}

Animal operator+ (const Animal& a1, const Animal& a2) {
    return Animal(0);
}

/* Virus */

Virus::Virus (string rna) : Genome(rna, "", "") {

}

void Virus::setVirus (string rna) {

}

Strand Virus::getVirus () const {
    return Strand("");
}

void Virus::mutateSmallScale (char n1, char n2, int m, int n) {

}

void Virus::mutateLargeScale (string s1, int n, string s2, int m) {

}

void Virus::mutateInversely (string s, int n) {

}

bool Virus::isPathogenic (const Animal& animal) const {
    return true;
}
