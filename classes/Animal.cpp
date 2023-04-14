#include <iostream>
#include "../libs/common.h"
#include "../libs/algorithms.h"
#include "Animal.h"

using namespace std;

/* Animal */

/*
    The constructor of Animal class
    Inputs:
        n : int
            Maximum number of chromosomes
*/
Animal::Animal (int n) : Cell(n) {}

/*
    This method kills the abnormal chromosomes.
*/
void Animal::killBadChromosomes () {
    auto i = chromosomes.begin();
    while (i != chromosomes.end()) {
        Chromosome c(**i);

        if (c.isAbnormal())
            i = chromosomes.erase(i);
        else
            ++i;
    }
    number = chromosomes.size();
}

/*
    This method returns a score of genetic similarity between the two animals.
    Algorithms:
        Modified Hausdorff Similarity
        Normalized Levenstein Distance
    Inputs:
        animal : Animal
            The animal which will be compared to
    Output:
        similarity : double
            The similarity score
*/
double Animal::getGeneticSimilarity (const Animal& animal) const {
    vector<pair<string, string>> a, b;

    for (auto &&i : chromosomes) {
        pair<Strand, Strand> dna = i -> getChromosome();
        a.push_back(
            {
                dna.first.getStrand(),
                dna.second.getStrand()
            }
        );
    }
    
    for (auto &&i : animal.chromosomes) {
        pair<Strand, Strand> dna = i -> getChromosome();
        b.push_back(
            {
                dna.first.getStrand(),
                dna.second.getStrand()
            }
        );
    }
    
    return computeMHS(a, b);
}

/*
    This method performs asexual reproduction.
    It is guaranteed that the animal will have at least 0.7 genetic similarity with its parent.
    Algorithms:
        Modified Hausdorff Similarity
        Normalized Levenstein Distance
    Output:
        child : Animal*
            A pointer to the reproduced child
*/
Animal* Animal::reproduceAsexually () const {
    Animal* child = new Animal(2 * number);

    for (int i = 0; i < 2; i++) {
        for (auto &&j : chromosomes) {
            pair<Strand, Strand> dna = j -> getChromosome();
            child -> addChromosome(dna.first.getStrand(), dna.second.getStrand());
        }
    }

    for (int i = 0; i < number; i++)
        iter_swap(
            (child -> chromosomes).begin() + randint(number, 2 * number - 1),
            (child -> chromosomes).begin() + randint(0, number - 1)
        );

    for (int i = 0; i < number; i++)
        (child -> chromosomes).pop_back();

    child -> number = number;

    if (Animal::getGeneticSimilarity(*child) <= SIMILARITY_THRESHOLD)
        return Animal::reproduceAsexually();
    else
        return child;
}

/*
    This overloaded operator checks if two animals are of the same species or not.
    Two animals are considered of the same species if their genetic similarity is above 0.7.
    Algorithms:
        Modified Hausdorff Similarity
        Normalized Levenstein Distance
    Output:
        equality : bool
            Are the animals of the same species or not?
*/
bool operator== (const Animal& a1, const Animal& a2) {
    if (a1.number == a2.number)
        if (a1.getGeneticSimilarity(a2) > SIMILARITY_THRESHOLD)
            return true;

    return false;
}

/*
    This overloaded operator preforms sexual reproduction.
    It is guaranteed that the animal will have at least 0.7 genetic similarity with each of its parents.
    Algorithms:
        Modified Hausdorff Similarity
        Normalized Levenstein Distance
    Output:
        child : Animal*
            A pointer to the reproduced child
*/
Animal* operator+ (const Animal& a1, const Animal& a2) {
    if (a1.number != a2.number)
        return new Animal((a1.number + a2.number) / 2);
    
    Animal* c1 = a1.reproduceAsexually();
    Animal* c2 = a2.reproduceAsexually();

    Animal* child = new Animal(c1 -> number);

    if (randint(1, 2) == 1)
        swap(c1, c2);

    for (int i = 0; i < child -> number; i++) {
        int index = randint(0, (c1 -> chromosomes).size() - 1);
        pair<Strand, Strand> dna = (c1 -> chromosomes).at(index) -> getChromosome();
        child -> addChromosome(dna.first.getStrand(), dna.second.getStrand());
        swap(c1, c2);
    }

    for (int i = 0; i < child -> number; i++)
        iter_swap(
            (child -> chromosomes).begin() + randint(0, child -> number - 1),
            (child -> chromosomes).begin() + randint(0, child -> number - 1)
        );

    if (a1.getGeneticSimilarity(*child) > SIMILARITY_THRESHOLD && a2.getGeneticSimilarity(*child) > SIMILARITY_THRESHOLD)
        return child;
    else
        return a1 + a2;
}

/* Virus */

/*
    The constructor of Virus class
    Inputs:
        rna : string
            The RNA strand
*/
Virus::Virus (string rna) : Genome(rna, "", "") {}

/*
    This method sets the RNA strand of the virus.
    Inputs:
        rna : string
            The RNA strand
*/
void Virus::setVirus (string rna) {
    Virus::setRNA(rna);
}

/*
    This method returns the Strand instance of virus RNA.
    Output:
        rna : Strand
            The Strand instance of RNA
*/
Strand Virus::getVirus () const {
    return Virus::getRNA();
}

/*
    This method mutates n first nucleotides n1 within virus RNA into nucleotides n2.
    Inputs:
        n1 : char
            The nucleotide which will be mutated
        n2 : char
            The nucleotide wich will be mutated into
        n : int (default: -1)
            Number of mutations (every occurrence will be mutated if -1)
*/
void Virus::mutateSmallScale (char n1, char n2, int n) {
    Virus::mutateSmallScaleRNA(n1, n2, n);
}

/*
    This method mutates a chunk of nucleotides s1 within virus RNA into another chunk s2.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s1 : string
            The chunk of nucleotides which will be mutated
        s2 : string
            The chunk of nucleotides which will be mutated into
*/
void Virus::mutateLargeScale (string s1, string s2) {
    Virus::mutateLargeScaleRNA(s1, s2);
}

/*
    This method reverses a chunk of nucleotides within virus RNA.
    Algorithms:
        Knuth-Morris-Pratt (KMP) Pattern Searching
    Inputs:
        s : string
            The chunk of nucleotides which will be reversed
*/
void Virus::mutateInversely (string s) {
    Virus::mutateInverselyRNA(s);
}

/*
    This method checks if the virus is pathogenic for a specific animal or not.
    Algorithms:
        Longest Common Substring (LCS) between Multiple Strings
    Inputs:
        animal : Animal
            The animal that the pathogenicity will be checked for
    Output:
        pathogenicity : bool
            The pathogenicity state of the virus for the animal
*/
bool Virus::isPathogenic (const Animal& animal) const {
    for (int i = 0; i < 2; i++) {
        vector<string> strings;

        for (auto &&j : animal.chromosomes) {
            pair<Strand, Strand> dna = j -> getChromosome();
            if (i == 0)
                strings.push_back(dna.first.getStrand());
            else
                strings.push_back(dna.second.getStrand());
        }
        
        string lcs = findLCS(strings);

        string r = rna -> getStrand();

        if (lcs != "")
            if (findPattern(r, lcs) != -1 || findPattern(r, getStrandComplement(lcs)) != -1)
                return true;
    }
    
    return false;
}