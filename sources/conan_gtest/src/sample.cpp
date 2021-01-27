#include "sample.h"

int get_42()
{
    return 42;
}

std::string get_hello()
{
    // NOTE: This roundabout implementation is only to show
    // use of the Conan package boost.
    std::string H = "HELLO";
    boost::algorithm::to_lower(H);
    return H;
}
