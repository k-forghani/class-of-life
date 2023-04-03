#include <iostream>
#include "Interface.h"

using namespace std;

/* File */

File::File (string path) {

}

void File::write (string content) const {

}

string File::read () const {

}

/* FastA */

FastA::FastA (string path) : File(path) {

}

void FastA::dump (map<string, string> content) const {

}

map<string, string> FastA::parse () const {

}

/* Text */

Text::Text(string text, string foreground, string background, set<string> modes) {

}

ostream& operator<< (ostream& output, const Text& text) {

}

istream& operator>> (istream& input, const Text& text) {

}

Text operator+ (const Text& t1, const Text& t2) {

}

/* Log */

Log::Log (string type, const Text& text) {

}

void Log::print(bool type) const {

}

/* Logger */

Logger::Logger (string root, bool type) {

}

void Logger::log (string type, Text text, bool print) const {

}

/* Workspace */

/* Interface */
