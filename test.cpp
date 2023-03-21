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

    /* mutateSmallScaleDNA() */

    cout << endl << "mutateSmallScaleDNA()" << endl;

    genome.mutateSmallScaleRNA('g', 'a', 2);
    cout << genome.getRNA().getStrand() << endl;

    return 0;
}