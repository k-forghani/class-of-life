#include <iostream>
#include "Cell.h"

using namespace std;

/* Strand */

void Strand::normalize () {

}

bool Strand::validate () const {

}

Strand::Strand (string strand) {

}

void Strand::set (string strand) {

}

string Strand::get () const {

}

/* Genome */

Genome::Genome (string rna, string dnaf, string dnas) {

}

void Genome::setRNA (string s) {

}

void Genome::setDNA (string s1, string s2) {

}

Strand* Genome::getRNA () const {

}

pair<Strand*, Strand*> Genome::getDNA () const {

}

pair<Strand*, Strand*> Genome::transformRNAtoDNA () const {

}

void Genome::mutateSmallScaleRNA (char n1, char n2, int n = -1) {

}

void Genome::mutateSmallScaleDNA (char n1, char n2, int n = -1) {

}

void Genome::mutateLargeScaleRNA (string s1, string s2) {

}

void Genome::mutateLargeScaleDNA (string s1, string s2) {

}

void Genome::mutateInverselyRNA (string s) {

}

void Genome::mutateInverselyDNA (string s) {

}

/* Chromosome */

Chromosome::Chromosome (string s1, string s2) : Genome("", s1, s2) {

}

void Chromosome::set (string s1, string s2) {

}

pair<Strand*, Strand*> Chromosome::get () const {

}

void Chromosome::mutateSmallScale (char n1, char n2, int n = -1) {

}

void Chromosome::mutateLargeScale (string s1, string s2) {

}

void Chromosome::mutateInversely (string s) {

}

/* Cell */

Cell::Cell (int n) {

}

void Cell::addChromosome (const Chromosome& c) {

}

void Cell::dieIfShould () {

}

void Cell::mutateSmallScale (char n1, char n2, int m, int n = -1) {

}

void Cell::mutateLargeScale (string s1, int n, string s2, int m) {

}

void Cell::mutateInversely (string s, int n) {

}

void Cell::printComplementaryPalindromes () const {

}
