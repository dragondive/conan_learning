#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>

// NOTE: The best practice is to include below header only in the cpp file.
// Included here only to show the difference between "requires" dependency
// and "build_requires" dependency with a simple example.
#include <boost/algorithm/string.hpp>

/**
  * Get the number 42\n
  * Runs in &Theta;(1)
  *
  * @return 42
  *
  * @see https://en.wikipedia.org/wiki/42_(number)#The_Hitchhiker's_Guide_to_the_Galaxy
  *
  * @startuml
  * actor user
  * participant sample
  *
  * user -> sample : call get_42()
  * user <- sample : 42
  * @enduml
  */
int get_42();

/**
  * Get the string "Hello"\n
  * Runs in &Theta;(1)
  *
  * @return "Hello"
  *
  * @startuml
  * actor user
  * participant sample
  *
  * user -> sample : call get_hello()
  * user <- sample : "Hello"
  * @enduml
  */
std::string get_hello();

#endif
