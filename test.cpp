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
        "acgtacgtggccacgt",
        "tgcatgcaccggtgca"
    );
    cell -> addChromosome(
        "acgtacgtggccacgt",
        "tgcatgcaccggtgca"
    );

    /* mutateSmallScale() */
    
    cout << endl << "First chromosome after mutateSmallScale()" << endl;
    cell -> mutateSmallScale('a', 'c', 0, 1);
    Chromosome* c = (cell -> getChromosomes()).at(0);
    c -> printDNA();

    /* dieIfShould() */

    cell -> dieIfShould();
    
    return 0;
}