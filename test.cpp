#include <iostream>
#include <cstdlib>
#include "classes/Cell.h"
#include "classes/Animal.h"
#include "classes/Interface.h"
#include "libs/common.h"
#include "libs/io.h"

using namespace std;

void printRNA (const Genome& object) {
    cout << "RNA: " << object.getRNA().getStrand() << endl;
}

void printDNA (const Genome& object) {
    cout << "DNA:\n" << object.getDNA().first.getStrand() << endl << object.getDNA().second.getStrand() << endl;
}

int main () {
    /* Random Seed */

    srand(time(NULL));
    


    cout << endl << Text("--- Genome ---", "yellow") << endl;

    Genome genome(
        "gactacggat",
        "gatacacacc",
        "gtggggagct"
    );

    /* Initial Things */

    printRNA(genome);
    printDNA(genome);

    /* transformRNAtoDNA() */

    cout << endl << Text("transformRNAtoDNA()", "yellow") << endl;
    pair<Strand, Strand> dna = genome.transformRNAtoDNA();
    printDNA(genome);

    /* mutateSmallScaleRNA() */

    cout << endl << Text("mutateSmallScaleRNA()", "yellow") << endl;
    genome.mutateSmallScaleRNA('g', 'a', 2);
    printRNA(genome);

    /* mutateSmallScaleDNA */

    cout << endl << Text("mutateSmallScaleDNA()", "yellow") << endl;
    genome.mutateSmallScaleDNA('g', 'a', -1);
    printDNA(genome);

    /* mutateLargeScaleRNA() */

    cout << endl << Text("mutateLargeScaleRNA()", "yellow") << endl;
    genome.mutateLargeScaleRNA("aac", "tt");
    printRNA(genome);

    /* mutateLargeScaleDNA() */

    cout << endl << Text("mutateLargeScaleDNA()", "yellow") << endl;
    genome.mutateLargeScaleDNA("ac", "gg");
    printDNA(genome);

    /* mutateInverselyRNA() */
    
    cout << endl << Text("mutateInverselyRNA()", "yellow") << endl;
    genome.mutateInverselyRNA("gat");
    printRNA(genome);

    /* mutateInverselyDNA() */
    
    cout << endl << Text("mutateInverselyDNA()", "yellow") << endl;
    genome.mutateInverselyDNA("aatt");
    printDNA(genome);



    cout << endl << Text("--- Cell ---", "green") << endl;

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
    
    cout << endl << Text("First chromosome after mutateSmallScale()", "green") << endl;
    cell -> mutateSmallScale('a', 'c', 0, 1);
    Chromosome* c = (cell -> getChromosomes()).at(0);
    printDNA(*c);

    /* mutateLargeScale() */
    
    cout << endl << Text("mutateLargeScale()", "green") << endl;
    cell -> mutateLargeScale("gta", 1, "gac", 2);
    Chromosome* c1 = (cell -> getChromosomes()).at(1);
    Chromosome* c2 = (cell -> getChromosomes()).at(2);
    cout << "Chromosome 1:" << endl;
    printDNA(*c1);
    cout << "Chromosome 2:" << endl;
    printDNA(*c2);

    /* mutateInversely() */
    
    cout << endl << Text("Second chromosome after mutateInversely()", "green") << endl;
    cell -> mutateInversely("gac", 1);
    Chromosome* cp = (cell -> getChromosomes()).at(1);
    printDNA(*cp);

    /* getComplementaryPalindromes() */
    
    cout << endl << Text("getComplementaryPalindromes()", "green") << endl;
    vector<vector<string>> result = cell -> getComplementaryPalindromes();

    string chromosome_index = "0";
    string strand_index = "0";
    for (auto &&i : result) {
        if (i.at(0) != chromosome_index) {
            cout << "Chromosome " << i.at(0) << endl;
            chromosome_index = i.at(0);
        }
        if (i.at(1) != strand_index) {
            cout << "\tStrand " << i.at(1) << endl;
            strand_index = i.at(1);
        }
        cout << "\t\t" << i.at(2) << "-" << i.at(3) << "\t" << i.at(4) << endl;
    }
    
    /* dieIfShould() */

    cell -> dieIfShould();



    cout << endl << Text("--- Animal ---", "blue") << endl;

    Animal a1(1);
    Animal a2(1);
    a1.addChromosome(
        "ttggcccattagctaa",
        "actgactgcatgactgcatg"
    );
    a2.addChromosome(
        "ttggcccattagctaa",
        "actgactgca"
    );

    /* getGeneticSimilarity() */

    cout << endl << Text("getGeneticSimilarity()", "blue") << endl;
    cout << a1.getGeneticSimilarity(a2) << endl;

    /* operator == */

    cout << endl << Text("operator ==", "blue") << endl;
    cout << to_string(a1 == a2) << endl;

    /* killBadChromosomes() */

    cout << endl << Text("killBadChromosomes()", "blue") << endl;
    a1.killBadChromosomes();
    cout << "Number of Chromosomes: " << a1.getChromosomes().size() << endl;



    Animal parent(5);
    parent.addChromosome("acgtgacgt", "tgcactgca");
    parent.addChromosome("gtacgataa", "catgctatt");
    parent.addChromosome("cgtagccct", "gcatcggga");
    parent.addChromosome("tgatacgtg", "actatgcac");
    parent.addChromosome("ggtactcag", "ccatgagtc");

    /* reproduceAsexually() */

    cout << endl << Text("reproduceAsexually()", "blue") << endl;
    Animal* child = parent.reproduceAsexually();
    cout << "Similarity with Parent: " << child -> getGeneticSimilarity(parent) << endl;

    /* operator + */

    cout << endl << Text("operator +", "blue") << endl;
    Animal* baby = a1 + a2;
    cout << "Similarity with Parent 1: " << baby -> getGeneticSimilarity(parent) << endl;
    cout << "Similarity with Parent 2: " << baby -> getGeneticSimilarity(*child) << endl;



    cout << endl << Text("--- Virus ---", "magenta") << endl;

    Virus virus("gttagctgtacgt");

    /* Initial Things */

    printRNA(virus);

    /* mutateSmallScale() */

    cout << endl << Text("mutateSmallScale()", "magenta") << endl;
    virus.mutateSmallScale('t', 'g', 2);
    printRNA(virus);

    /* mutateLargeScale() */

    cout << endl << Text("mutateLargeScale()", "magenta") << endl;
    virus.mutateLargeScale("gtacgt", "aaaaaa");
    printRNA(virus);

    /* mutateInversely() */
    
    cout << endl << Text("mutateInversely()", "magenta") << endl;
    virus.mutateInversely("ct");
    printRNA(virus);



    Virus pathogen("gtggctagcac");

    Animal host(5);
    host.addChromosome("gctagccgatcgaa", "tgcactgcacatgc");
    host.addChromosome("cgatccatgctagc", "catgctaacgtgtt");
    host.addChromosome("actggagtgctagc", "gcatcgggcagcca");
    host.addChromosome("agtgctagcagttg", "actatgtacggcac");
    host.addChromosome("aaagctagcagtgg", "cccgtacatgagtc");

    /* isPathogenic() */

    cout << endl << Text("isPathogenic()", "magenta") << endl;
    cout << pathogen.isPathogenic(host) << endl;



    /* Text */

    cout << endl << Text("--- Text ---", "blue") << endl;
    cout << Text("Enter something: ", "red");
    Text text("", "green", "", {"bold", "blinking"});
    cin >> text;
    cout << Text("You have entered ", "yellow") + text + Text(".", "yellow") << endl;

    /* Log */

    cout << endl << Text("--- Log ---", "green") << endl;
    Log log(
        "info",
        new Text("Program started!")
    );
    log.print(true);

    /* FastA */

    cout << endl << Text("--- FastA ---", "cyan") << endl;

    map<string, string> records = parseFastA("samples/genomes.fasta");
    for (const auto &i : records) {
        cout << ">" << i.first << endl;
        cout << i.second << endl;
        cout << endl;
    }

    records.erase("g3 dnaf");
    records.erase("g3 dnas");
    records.erase("g3 rna");

    writeFastA(records, "samples/genomes.temp.fasta");



    Workspace ws("CoL");

    /* Workspace Genome */

    cout << Text("--- Workspace Genome ---", "red") << endl;
    ws.genomes["g1"] = new Genome(
        "gactacggatgatcagcatcatcagcgactactagcgcgctatcgactacgactactatatagcgatcatctacgactactagcagctactacgacgcgctagcga",
        "gatgtacgatatagccctagctatataggtctagatacgctagcgcgcgcgctatatatatcgctacgactacgatagctctagctatctagcgatctattacacc",
        "gactatcagcatcattataagctactacgactctacgactactagcactatcgacgacgatcattatacgactacgatctactagcgatctatatagacgctatct"
    );
    ws.showGenome("g1", "extended");
    ws.showGenome("g1", "compact");

    /* Workspace Cell */

    cout << endl << Text("--- Workspace Cell ---", "red") << endl;
    ws.cells["c1"] = new Cell(3);
    ws.cells["c1"] -> addChromosome(
        "acgtacgtgggatcaggctacgactatcgatcagacgactatcaggctctagcttctatagcgccgactatcagctatacccacgt",
        "gactacgagctactactactacgatcatcagcatctgatcatcgactactaactctctcgagagagacttacgcatcatcagcagc"
    );
    ws.cells["c1"] -> addChromosome(
        "gtacgacttatg",
        "acgtgcacgacc"
    );
    ws.cells["c1"] -> addChromosome(
        "acgtgg",
        "ggtgac"
    );
    ws.showCell("c1", "extended");
    ws.showCell("c1", "compact");

    /* Workspace Animal */

    ws.animals["a1"] = new Animal(1);
    ws.animals["a1"] -> addChromosome(
        "gatctacgactac",
        "gatctacgaccct"
    );
    ws.showAnimal("a1", "extended");
    ws.showAnimal("a1", "compact");

    /* Workspace Virus */

    cout << endl << Text("--- Workspace Virus ---", "red") << endl;
    ws.viruses["v1"] = new Virus(
        "gactacgatcactacacggactactgacgcgcgctacgactacgactgactacgatcgacgtactactgatctacgactacttatatagctctatatatcgcctctatagatc"
    );
    ws.showVirus("v1", "extended");
    ws.showVirus("v1", "compact");

    /* Workspace Genomes List */
    
    cout << endl << Text("--- Workspace Genomes List ---", "red") << endl;
    ws.genomes["g2"] = new Genome(
        "gatctacgatc",
        "tgagctactac",
        "gactatcgact"
    );
    ws.listGenomes();

    /* Workspace Cells List */
    
    cout << endl << Text("--- Workspace Cells List ---", "red") << endl;
    ws.listCells();

    /* Workspace Animals List */
    
    cout << endl << Text("--- Workspace Animals List ---", "red") << endl;
    ws.listAnimals();

    /* Workspace Viruses List */
    
    cout << endl << Text("--- Workspace Viruses List ---", "red") << endl;
    ws.listViruses();
    
    return 0;
}