#include <iostream>
#include <cstdlib>
#include "Cell.h"
#include "Animal.h"

using namespace std;

int main () {

    /* Random Seed */

    srand(time(NULL));



    Genome genome(
        "gactacggat",
        "gatacacacc",
        "gtggggagct"
    );

    /* Initial Things */

    genome.printRNA("RNA: ");
    genome.printDNA("DNA:\n");

    /* transformRNAtoDNA() */

    cout << endl << "transformRNAtoDNA()" << endl;
    pair<Strand, Strand> dna = genome.transformRNAtoDNA();
    genome.printDNA("DNA:\n");

    /* mutateSmallScaleRNA() */

    cout << endl << "mutateSmallScaleRNA()" << endl;
    genome.mutateSmallScaleRNA('g', 'a', 2);
    genome.printRNA("RNA: ");

    /* mutateSmallScaleDNA */

    cout << endl << "mutateSmallScaleDNA()" << endl;
    genome.mutateSmallScaleDNA('g', 'a', -1);
    genome.printDNA("DNA:\n");

    /* mutateLargeScaleRNA() */

    cout << endl << "mutateLargeScaleRNA()" << endl;
    genome.mutateLargeScaleRNA("aac", "tt");
    genome.printRNA("RNA: ");

    /* mutateLargeScaleDNA() */

    cout << endl << "mutateLargeScaleDNA()" << endl;
    genome.mutateLargeScaleDNA("ac", "gg");
    genome.printDNA("DNA:\n");

    /* mutateInverselyRNA() */
    
    cout << endl << "mutateInverselyRNA()" << endl;
    genome.mutateInverselyRNA("gat");
    genome.printRNA("RNA: ");

    /* mutateInverselyDNA() */
    
    cout << endl << "mutateInverselyDNA()" << endl;
    genome.mutateInverselyDNA("aatt");
    genome.printDNA("DNA:\n");



    Cell* cell = new Cell(3);
    cell -> addChromosome(
        "acgtacgtggccacgt",
        "tgcatgcaccggtgca"
    );
    cell -> addChromosome(
        "gtacgacttatg",
        "acgtgcacgacc"
    );
    cell -> addChromosome(
        "acgtgg",
        "ggtgac"
    );

    /* mutateSmallScale() */
    
    cout << endl << "First chromosome after mutateSmallScale()" << endl;
    cell -> mutateSmallScale('a', 'c', 0, 1);
    Chromosome* c = (cell -> getChromosomes()).at(0);
    c -> printDNA();

    /* mutateLargeScale() */
    
    cout << endl << "mutateLargeScale()" << endl;
    cell -> mutateLargeScale("gta", 1, "gac", 2);
    Chromosome* c1 = (cell -> getChromosomes()).at(1);
    Chromosome* c2 = (cell -> getChromosomes()).at(2);
    cout << "Chromosome 1:" << endl;
    c1 -> printDNA();
    cout << "Chromosome 2:" << endl;
    c2 -> printDNA();

    /* mutateInversely() */
    
    cout << endl << "Second chromosome mutateInversely()" << endl;
    cell -> mutateInversely("gac", 1);
    Chromosome* cp = (cell -> getChromosomes()).at(1);
    cp -> printDNA();

    /* printComplementaryPalindromes() */
    
    cout << endl << "printComplementaryPalindromes()" << endl;
    cell -> printComplementaryPalindromes();

    /* dieIfShould() */

    cell -> dieIfShould();



    Animal a1(1);
    Animal a2(1);
    a1.addChromosome(
        "ttggcccattagctaa",
        "aacggtttagccccgg"
    );
    a2.addChromosome(
        "ttggcccattagctaa",
        "gacggtttatacta"
    );

    /* getGeneticSimilarity() */

    cout << endl << "getGeneticSimilarity()" << endl;
    cout << a1.getGeneticSimilarity(a2) << endl;

    /* operator == */

    cout << endl << "operator ==" << endl;
    cout << to_string(a1 == a2) << endl;

    /* killBadChromosomes() */

    cout << endl << "killBadChromosomes()" << endl;
    a1.killBadChromosomes();
    cout << "Number of Chromosomes: " << a1.getChromosomes().size() << endl;



    Animal parent(5);
    parent.addChromosome("acgtgacgt", "tgcactgca");
    parent.addChromosome("gtacgataa", "catgctatt");
    parent.addChromosome("cgtagccct", "gcatcggga");
    parent.addChromosome("tgatacgtg", "actatgcac");
    parent.addChromosome("ggtactcag", "ccatgagtc");

    /* reproduceAsexually() */

    cout << endl << "reproduceAsexually()" << endl;
    Animal child = parent.reproduceAsexually();
    cout << "Similarity with Parent: " << child.getGeneticSimilarity(parent) << endl;

    /* operator + */

    a1 = parent;
    a2 = child;
    cout << endl << "operator +" << endl;
    Animal baby = a1 + a2;
    cout << "Similarity with Parent 1: " << baby.getGeneticSimilarity(a1) << endl;
    cout << "Similarity with Parent 2: " << baby.getGeneticSimilarity(a2) << endl;



    Virus virus("gttagctgtacgt");

    /* Initial Things */

    virus.printRNA("RNA: ");

    /* mutateSmallScale() */

    cout << endl << "mutateSmallScale()" << endl;
    virus.mutateSmallScale('t', 'g', 2);
    virus.printRNA("RNA: ");

    /* mutateLargeScale() */

    cout << endl << "mutateLargeScale()" << endl;
    virus.mutateLargeScale("gtacgt", "aaaaaa");
    virus.printRNA("RNA: ");

    /* mutateInversely() */
    
    cout << endl << "mutateInversely()" << endl;
    virus.mutateInversely("ct");
    virus.printRNA("RNA: ");



    Virus pathogen("gtggctagcac");

    Animal host(5);
    host.addChromosome("gctagccgatcgaa", "tgcactgcacatgc");
    host.addChromosome("cgatccatgctagc", "catgctaacgtgtt");
    host.addChromosome("actggagtgctagc", "gcatcgggcagcca");
    host.addChromosome("agtgctagcagttg", "actatgtacggcac");
    host.addChromosome("aaagctagcagtgg", "cccgtacatgagtc");

    /* isPathogenic() */

    cout << endl << "isPathogenic()" << endl;
    cout << pathogen.isPathogenic(host) << endl;
    
    return 0;
}