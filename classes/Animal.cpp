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
    double similarity = 0;

    for (int i = 0; i < 3; i++) {
        vector<string> a;
        vector<string> b;

        for (auto j = chromosomes.begin(); j != chromosomes.end(); ++j) {
            pair<Strand, Strand> dna = (**j).getChromosome();
            if (i == 0 || i == 1)
                a.push_back(dna.first.getStrand());
            else if (i == 2 || i == 3)
                a.push_back(dna.second.getStrand());
        }
        
        for (auto j = animal.chromosomes.begin(); j != animal.chromosomes.end(); ++j) {
            pair<Strand, Strand> dna = (**j).getChromosome();
            if (i == 0 || i == 2)
                b.push_back(dna.first.getStrand());
            else if (i == 1 || i == 3)
                b.push_back(dna.second.getStrand());
        }

        double score = computeMHS(a, b);

        if (score > similarity)
            similarity = score;
    }
    
    return similarity;
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
    if (a1.number != a2.number)
        return false;

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
        return (new Animal((int)((a1.number + a2.number) / 2)));
    
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

    for (int i = 0; i < child -> number; i++) {
        int source = randint(0, child -> number - 1);
        int target = randint(0, child -> number - 1);
        iter_swap(
            (child -> chromosomes).begin() + source,
            (child -> chromosomes).begin() + target
        );
    }

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

        for (auto j = animal.chromosomes.begin(); j != animal.chromosomes.end(); ++j) {
            pair<Strand, Strand> dna = (**j).getChromosome();
            if (i == 0)
                strings.push_back(dna.first.getStrand());
            else
                strings.push_back(dna.second.getStrand());
        }
        
        string lcs = findLCS(strings);

        string r = rna -> getStrand();

        if (lcs != "" && (findPattern(r, lcs) || findPattern(r, getStrandComplement(lcs))))
            return true;
    }
    
    return false;
}