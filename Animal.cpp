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
    Animal* child = new Animal(2 * number);

    for (int i = 0; i < 2; i++) {
        for (auto i = chromosomes.begin(); i != chromosomes.end(); ++i) {
            pair<Strand, Strand> dna = (**i).getChromosome();
            child -> addChromosome(dna.first.getStrand(), dna.second.getStrand());
        }
    }

    for (int i = 0; i < number; i++) {
        int source = randint(number, 2 * number - 1);
        int target = randint(0, number - 1);
        iter_swap(
            (child -> chromosomes).begin() + source,
            (child -> chromosomes).begin() + target
        );
    }

    for (int i = 0; i < number; i++) {
        (child -> chromosomes).pop_back();
    }

    child -> number = number;

    if (Animal::getGeneticSimilarity(*child) <= SIMILARITY_THRESHOLD) {
        return Animal::reproduceAsexually();
    } else {
        return *child;
    }
}

bool operator== (const Animal& a1, const Animal& a2) {
    if (a1.number != a2.number) {
        return false;
    }

    if (a1.getGeneticSimilarity(a2) > SIMILARITY_THRESHOLD) {
        return true;
    }

    return false;
}

Animal operator+ (const Animal& a1, const Animal& a2) {
    if (a1.number != a2.number) {
        return Animal((int)((a1.number + a2.number) / 2));
    }

    Animal c1 = a1.reproduceAsexually();
    Animal c2 = a2.reproduceAsexually();

    Animal* child = new Animal(c1.number);

    Animal* current;
    Animal* next;

    if (randint(1, 2) == 1) {
        current = &c1;
        next = &c2;
    } else {
        current = &c2;
        next = &c1;
    }

    for (int i = 0; i < child -> number; i++) {
        int index = randint(0, (current -> chromosomes).size() - 1);
        pair<Strand, Strand> dna = (current -> chromosomes).at(index) -> getChromosome();
        child -> addChromosome(dna.first.getStrand(), dna.second.getStrand());
        swap(current, next);
    }


    for (int i = 0; i < child -> number; i++) {
        int source = randint(0, child -> number - 1);
        int target = randint(0, child -> number - 1);
        iter_swap(
            (child -> chromosomes).begin() + source,
            (child -> chromosomes).begin() + target
        );
    }

    if (a1.getGeneticSimilarity(*child) > 0.7 && a2.getGeneticSimilarity(*child) > 0.7) {
        return *child;
    } else {
        return a1 + a2;
    }
}

/* Virus */

Virus::Virus (string rna) : Genome(rna, "", "") {}

void Virus::setVirus (string rna) {
    Virus::setRNA(rna);
}

Strand Virus::getVirus () const {
    return Virus::getRNA();
}

void Virus::mutateSmallScale (char n1, char n2, int n) {
    Virus::mutateSmallScaleRNA(n1, n2, n);
}

void Virus::mutateLargeScale (string s1, string s2) {
    Virus::mutateLargeScaleRNA(s1, s2);
}

void Virus::mutateInversely (string s) {
    Virus::mutateInverselyRNA(s);
}

bool Virus::isPathogenic (const Animal& animal) const {
    for (int i = 0; i < 2; i++) {
        vector<string> strings;

        for (auto j = animal.chromosomes.begin(); j != animal.chromosomes.end(); ++j) {
            pair<Strand, Strand> dna = (**j).getChromosome();
            if (i == 0) {
                strings.push_back(dna.first.getStrand());
            } else {
                strings.push_back(dna.second.getStrand());
            }
        }
        
        string lcs = findLCS(strings);

        string r = rna -> getStrand();

        if (lcs != "" && (findPattern(r, lcs) || findPattern(r, getStrandComplement(lcs)))) {
            return true;
        }
    }
    
    return false;
}
