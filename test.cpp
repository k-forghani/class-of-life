#include <iostream>
#include "Cell.h"
#include "Animal.h"

using namespace std;

int main () {
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
    
    return 0;
}