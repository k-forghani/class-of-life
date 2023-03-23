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
    cout << "RNA: " << endl << genome.getRNA().getStrand() << endl;
    cout << "DNA: " << endl << genome.getDNA().first.getStrand() << endl << genome.getDNA().second.getStrand() << endl;

    /* transformRNAtoDNA() */

    cout << endl << "transformRNAtoDNA()" << endl;
    pair<Strand, Strand> dna = genome.transformRNAtoDNA();
    cout << "DNA: " << endl << genome.getDNA().first.getStrand() << endl << genome.getDNA().second.getStrand() << endl;

    /* mutateSmallScaleRNA() */

    cout << endl << "mutateSmallScaleRNA()" << endl;
    genome.mutateSmallScaleRNA('g', 'a', 2);
    cout << "RNA: " << endl << genome.getRNA().getStrand() << endl;

    /* mutateSmallScaleDNA */

    cout << endl << "mutateSmallScaleDNA()" << endl;
    genome.mutateSmallScaleDNA('g', 'a', -1);
    cout << genome.getDNA().first.getStrand() << endl << genome.getDNA().second.getStrand() << endl;

    /* mutateLargeScaleRNA() */

    cout << endl << "mutateLargeScaleRNA()" << endl;
    genome.mutateLargeScaleRNA("aac", "tt");
    cout << "RNA: " << endl << genome.getRNA().getStrand() << endl;

    /* mutateLargeScaleDNA() */

    cout << endl << "mutateLargeScaleDNA()" << endl;
    genome.mutateLargeScaleDNA("ac", "gg");
    cout << genome.getDNA().first.getStrand() << endl << genome.getDNA().second.getStrand() << endl;

    return 0;
}