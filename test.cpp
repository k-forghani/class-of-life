#include <iostream>
#include "Cell.h"
#include "Animal.h"

using namespace std;

int main () {
    /* transformRNAtoDNA() */

    cout << "transformRNAtoDNA()" << endl;

    Genome genome(
        "gactacggat",
        "gatacacacc",
        "gtggggagct"
    );
    pair<Strand, Strand> dna = genome.transformRNAtoDNA();
    cout << dna.first.getStrand() << endl << dna.second.getStrand() << endl;

    /* mutateSmallScaleRNA() */

    cout << endl << "mutateSmallScaleRNA()" << endl;

    genome.mutateSmallScaleRNA('g', 'a', 2);
    cout << genome.getRNA().getStrand() << endl;

    /* mutateSmallScaleDNA */

    cout << endl << "mutateSmallScaleDNA()" << endl;

    genome.mutateSmallScaleDNA('g', 'a', -1);
    cout << genome.getDNA().first.getStrand() << endl << genome.getDNA().second.getStrand() << endl;

    return 0;
}