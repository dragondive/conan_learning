#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>

// NOTE: The best practice is to include below header only in the cpp file.
// Included here only to show the difference between "requires" dependency
// and "build_requires" dependency with a simple example.

#include <boost/algorithm/string.hpp>

int get_42();
std::string get_hello();

#endif
